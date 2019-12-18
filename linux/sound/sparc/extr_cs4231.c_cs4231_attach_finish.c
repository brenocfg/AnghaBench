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
struct snd_cs4231 {TYPE_1__* op; } ;
struct snd_card {struct snd_cs4231* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct snd_cs4231*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_card_register (struct snd_card*) ; 
 int snd_cs4231_mixer (struct snd_card*) ; 
 int snd_cs4231_pcm (struct snd_card*) ; 
 int snd_cs4231_timer (struct snd_card*) ; 

__attribute__((used)) static int cs4231_attach_finish(struct snd_card *card)
{
	struct snd_cs4231 *chip = card->private_data;
	int err;

	err = snd_cs4231_pcm(card);
	if (err < 0)
		goto out_err;

	err = snd_cs4231_mixer(card);
	if (err < 0)
		goto out_err;

	err = snd_cs4231_timer(card);
	if (err < 0)
		goto out_err;

	err = snd_card_register(card);
	if (err < 0)
		goto out_err;

	dev_set_drvdata(&chip->op->dev, chip);

	dev++;
	return 0;

out_err:
	snd_card_free(card);
	return err;
}