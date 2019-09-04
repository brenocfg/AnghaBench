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
struct via82xx_modem {int dummy; } ;
struct snd_ac97 {int /*<<< orphan*/  num; struct via82xx_modem* private_data; } ;

/* Variables and functions */
 unsigned short AC97_GPIO_STATUS ; 
 int /*<<< orphan*/  GPI_STATUS ; 
 int /*<<< orphan*/  VIAREG (struct via82xx_modem*,int /*<<< orphan*/ ) ; 
 unsigned short VIA_REG_AC97_CMD_SHIFT ; 
 unsigned int VIA_REG_AC97_CODEC_ID_PRIMARY ; 
 unsigned int VIA_REG_AC97_CODEC_ID_SECONDARY ; 
 unsigned int VIA_REG_AC97_CODEC_ID_SHIFT ; 
 unsigned short VIA_REG_AC97_DATA_SHIFT ; 
 int /*<<< orphan*/  outl (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_via82xx_codec_ready (struct via82xx_modem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_via82xx_codec_xwrite (struct via82xx_modem*,unsigned int) ; 

__attribute__((used)) static void snd_via82xx_codec_write(struct snd_ac97 *ac97,
				    unsigned short reg,
				    unsigned short val)
{
	struct via82xx_modem *chip = ac97->private_data;
	unsigned int xval;
	if(reg == AC97_GPIO_STATUS) {
		outl(val, VIAREG(chip, GPI_STATUS));
		return;
	}	
	xval = !ac97->num ? VIA_REG_AC97_CODEC_ID_PRIMARY : VIA_REG_AC97_CODEC_ID_SECONDARY;
	xval <<= VIA_REG_AC97_CODEC_ID_SHIFT;
	xval |= reg << VIA_REG_AC97_CMD_SHIFT;
	xval |= val << VIA_REG_AC97_DATA_SHIFT;
	snd_via82xx_codec_xwrite(chip, xval);
	snd_via82xx_codec_ready(chip, ac97->num);
}