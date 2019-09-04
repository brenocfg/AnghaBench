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
struct snd_cs46xx {scalar_t__ amplifier_ctrl; TYPE_1__* card; int /*<<< orphan*/ * ac97; int /*<<< orphan*/  ac97_bus; } ;
struct snd_ac97_template {int num; int /*<<< orphan*/  scaps; int /*<<< orphan*/  private_free; struct snd_cs46xx* private_data; } ;
typedef  int /*<<< orphan*/  ac97 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_MASTER ; 
 int /*<<< orphan*/  AC97_RESET ; 
 int /*<<< orphan*/  AC97_SCAP_INV_EAPD ; 
 int CS46XX_SECONDARY_CODEC_INDEX ; 
 int ENXIO ; 
 scalar_t__ amp_voyetra ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct snd_ac97_template*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_ac97_mixer (int /*<<< orphan*/ ,struct snd_ac97_template*,int /*<<< orphan*/ *) ; 
 int snd_cs46xx_codec_read (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_cs46xx_codec_write (struct snd_cs46xx*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_cs46xx_mixer_free_ac97 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cs46xx_detect_codec(struct snd_cs46xx *chip, int codec)
{
	int idx, err;
	struct snd_ac97_template ac97;

	memset(&ac97, 0, sizeof(ac97));
	ac97.private_data = chip;
	ac97.private_free = snd_cs46xx_mixer_free_ac97;
	ac97.num = codec;
	if (chip->amplifier_ctrl == amp_voyetra)
		ac97.scaps = AC97_SCAP_INV_EAPD;

	if (codec == CS46XX_SECONDARY_CODEC_INDEX) {
		snd_cs46xx_codec_write(chip, AC97_RESET, 0, codec);
		udelay(10);
		if (snd_cs46xx_codec_read(chip, AC97_RESET, codec) & 0x8000) {
			dev_dbg(chip->card->dev,
				"secondary codec not present\n");
			return -ENXIO;
		}
	}

	snd_cs46xx_codec_write(chip, AC97_MASTER, 0x8000, codec);
	for (idx = 0; idx < 100; ++idx) {
		if (snd_cs46xx_codec_read(chip, AC97_MASTER, codec) == 0x8000) {
			err = snd_ac97_mixer(chip->ac97_bus, &ac97, &chip->ac97[codec]);
			return err;
		}
		msleep(10);
	}
	dev_dbg(chip->card->dev, "codec %d detection timeout\n", codec);
	return -ENXIO;
}