#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_card_sb16 {int /*<<< orphan*/  fm_res; } ;
struct snd_card {struct snd_card_sb16* private_data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 void** awe_port ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct snd_card*) ; 
 void** fm_port ; 
 void** port ; 
 int /*<<< orphan*/  request_region (int,int,char*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_sb16_card_new (struct device*,int,struct snd_card**) ; 
 int snd_sb16_probe (struct snd_card*,int) ; 

__attribute__((used)) static int snd_sb16_isa_probe1(int dev, struct device *pdev)
{
	struct snd_card_sb16 *acard;
	struct snd_card *card;
	int err;

	err = snd_sb16_card_new(pdev, dev, &card);
	if (err < 0)
		return err;

	acard = card->private_data;
	/* non-PnP FM port address is hardwired with base port address */
	fm_port[dev] = port[dev];
	/* block the 0x388 port to avoid PnP conflicts */
	acard->fm_res = request_region(0x388, 4, "SoundBlaster FM");
#ifdef SNDRV_SBAWE_EMU8000
	/* non-PnP AWE port address is hardwired with base port address */
	awe_port[dev] = port[dev] + 0x400;
#endif

	if ((err = snd_sb16_probe(card, dev)) < 0) {
		snd_card_free(card);
		return err;
	}
	dev_set_drvdata(pdev, card);
	return 0;
}