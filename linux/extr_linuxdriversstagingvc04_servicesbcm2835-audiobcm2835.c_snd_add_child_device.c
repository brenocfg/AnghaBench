#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct snd_card {int /*<<< orphan*/  longname; int /*<<< orphan*/  shortname; int /*<<< orphan*/  driver; struct bcm2835_chip* private_data; } ;
struct device {int dummy; } ;
struct bcm2835_chip {int /*<<< orphan*/  vchi_ctx; int /*<<< orphan*/  audio_mutex; struct device* dev; struct snd_card* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct bcm2835_audio_driver {int (* newpcm ) (struct bcm2835_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* newctl ) (struct bcm2835_chip*) ;int /*<<< orphan*/  route; int /*<<< orphan*/  shortname; int /*<<< orphan*/  longname; TYPE_1__ driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bcm2835_card_free ; 
 int /*<<< orphan*/  bcm2835_devm_free_vchi_ctx ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct bcm2835_chip*) ; 
 int devm_add_action (struct device*,int /*<<< orphan*/ ,struct snd_card*) ; 
 int /*<<< orphan*/  devres_find (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_card_new (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct snd_card**) ; 
 int snd_card_register (struct snd_card*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct bcm2835_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct bcm2835_chip*) ; 

__attribute__((used)) static int snd_add_child_device(struct device *dev,
				struct bcm2835_audio_driver *audio_driver,
				u32 numchans)
{
	struct bcm2835_chip *chip;
	struct snd_card *card;
	int err;

	err = snd_card_new(dev, -1, NULL, THIS_MODULE, sizeof(*chip), &card);
	if (err < 0) {
		dev_err(dev, "Failed to create card");
		return err;
	}

	chip = card->private_data;
	chip->card = card;
	chip->dev = dev;
	mutex_init(&chip->audio_mutex);

	chip->vchi_ctx = devres_find(dev,
				     bcm2835_devm_free_vchi_ctx, NULL, NULL);
	if (!chip->vchi_ctx) {
		err = -ENODEV;
		goto error;
	}

	strcpy(card->driver, audio_driver->driver.name);
	strcpy(card->shortname, audio_driver->shortname);
	strcpy(card->longname, audio_driver->longname);

	err = audio_driver->newpcm(chip, audio_driver->shortname,
		audio_driver->route,
		numchans);
	if (err) {
		dev_err(dev, "Failed to create pcm, error %d\n", err);
		goto error;
	}

	err = audio_driver->newctl(chip);
	if (err) {
		dev_err(dev, "Failed to create controls, error %d\n", err);
		goto error;
	}

	err = snd_card_register(card);
	if (err) {
		dev_err(dev, "Failed to register card, error %d\n", err);
		goto error;
	}

	dev_set_drvdata(dev, chip);

	err = devm_add_action(dev, bcm2835_card_free, card);
	if (err < 0) {
		dev_err(dev, "Failed to add devm action, err %d\n", err);
		goto error;
	}

	dev_info(dev, "card created with %d channels\n", numchans);
	return 0;

 error:
	snd_card_free(card);
	return err;
}