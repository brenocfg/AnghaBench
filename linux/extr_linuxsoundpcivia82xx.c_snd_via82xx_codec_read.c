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
struct via82xx {TYPE_1__* card; } ;
struct snd_ac97 {unsigned int num; struct via82xx* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short VIA_REG_AC97_CMD_SHIFT ; 
 unsigned int VIA_REG_AC97_CODEC_ID_SHIFT ; 
 unsigned int VIA_REG_AC97_PRIMARY_VALID ; 
 unsigned int VIA_REG_AC97_READ ; 
 unsigned int VIA_REG_AC97_SECONDARY_VALID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 scalar_t__ snd_via82xx_codec_valid (struct via82xx*,int) ; 
 unsigned int snd_via82xx_codec_xread (struct via82xx*) ; 
 int /*<<< orphan*/  snd_via82xx_codec_xwrite (struct via82xx*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned short snd_via82xx_codec_read(struct snd_ac97 *ac97, unsigned short reg)
{
	struct via82xx *chip = ac97->private_data;
	unsigned int xval, val = 0xffff;
	int again = 0;

	xval = ac97->num << VIA_REG_AC97_CODEC_ID_SHIFT;
	xval |= ac97->num ? VIA_REG_AC97_SECONDARY_VALID : VIA_REG_AC97_PRIMARY_VALID;
	xval |= VIA_REG_AC97_READ;
	xval |= (reg & 0x7f) << VIA_REG_AC97_CMD_SHIFT;
      	while (1) {
      		if (again++ > 3) {
			dev_err(chip->card->dev,
				"codec_read: codec %i is not valid [0x%x]\n",
				   ac97->num, snd_via82xx_codec_xread(chip));
		      	return 0xffff;
		}
		snd_via82xx_codec_xwrite(chip, xval);
		udelay (20);
		if (snd_via82xx_codec_valid(chip, ac97->num) >= 0) {
			udelay(25);
			val = snd_via82xx_codec_xread(chip);
			break;
		}
	}
	return val & 0xffff;
}