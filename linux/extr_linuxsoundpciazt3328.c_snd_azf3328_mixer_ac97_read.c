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
struct snd_azf3328 {TYPE_1__* card; } ;
struct snd_ac97 {struct snd_azf3328* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AC97_EXTENDED_ID 133 
#define  AC97_EXTENDED_STATUS 132 
#define  AC97_POWERDOWN 131 
#define  AC97_RESET 130 
#define  AC97_VENDOR_ID1 129 
#define  AC97_VENDOR_ID2 128 
 unsigned short AZF_AC97_REG_EMU_IO_READ ; 
 unsigned short AZF_AC97_REG_REAL_IO_READ ; 
 unsigned short AZF_AC97_REG_UNSUPPORTED ; 
 unsigned short AZF_REG_MASK ; 
 unsigned short IDX_MIXER_SOMETHING30H ; 
 unsigned short azf_emulated_ac97_caps ; 
 unsigned short azf_emulated_ac97_powerdown ; 
 int azf_emulated_ac97_vendor_id ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned short) ; 
 unsigned short snd_azf3328_mixer_ac97_map_reg_idx (unsigned short) ; 
 int /*<<< orphan*/  snd_azf3328_mixer_ac97_map_unsupported (struct snd_azf3328 const*,unsigned short,char*) ; 
 unsigned short snd_azf3328_mixer_inw (struct snd_azf3328 const*,unsigned short) ; 

__attribute__((used)) static unsigned short
snd_azf3328_mixer_ac97_read(struct snd_ac97 *ac97, unsigned short reg_ac97)
{
	const struct snd_azf3328 *chip = ac97->private_data;
	unsigned short reg_azf = snd_azf3328_mixer_ac97_map_reg_idx(reg_ac97);
	unsigned short reg_val = 0;
	bool unsupported = false;

	dev_dbg(chip->card->dev, "snd_azf3328_mixer_ac97_read reg_ac97 %u\n",
		reg_ac97);
	if (reg_azf & AZF_AC97_REG_UNSUPPORTED)
		unsupported = true;
	else {
		if (reg_azf & AZF_AC97_REG_REAL_IO_READ)
			reg_val = snd_azf3328_mixer_inw(chip,
						reg_azf & AZF_REG_MASK);
		else {
			/*
			 * Proceed with dummy I/O read,
			 * to ensure compatible timing where this may matter.
			 * (ALSA AC97 layer usually doesn't call I/O functions
			 * due to intelligent I/O caching anyway)
			 * Choose a mixer register that's thoroughly unrelated
			 * to common audio (try to minimize distortion).
			 */
			snd_azf3328_mixer_inw(chip, IDX_MIXER_SOMETHING30H);
		}

		if (reg_azf & AZF_AC97_REG_EMU_IO_READ) {
			switch (reg_ac97) {
			case AC97_RESET:
				reg_val |= azf_emulated_ac97_caps;
				break;
			case AC97_POWERDOWN:
				reg_val |= azf_emulated_ac97_powerdown;
				break;
			case AC97_EXTENDED_ID:
			case AC97_EXTENDED_STATUS:
				/* AFAICS we simply can't support anything: */
				reg_val |= 0;
				break;
			case AC97_VENDOR_ID1:
				reg_val = azf_emulated_ac97_vendor_id >> 16;
				break;
			case AC97_VENDOR_ID2:
				reg_val = azf_emulated_ac97_vendor_id & 0xffff;
				break;
			default:
				unsupported = true;
				break;
			}
		}
	}
	if (unsupported)
		snd_azf3328_mixer_ac97_map_unsupported(chip, reg_ac97, "read");

	return reg_val;
}