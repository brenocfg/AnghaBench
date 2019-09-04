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
#define  AC97_EXTENDED_STATUS 130 
#define  AC97_POWERDOWN 129 
#define  AC97_REC_GAIN_MIC 128 
 unsigned short AZF_AC97_REG_EMU_IO_WRITE ; 
 unsigned short AZF_AC97_REG_REAL_IO_WRITE ; 
 unsigned short AZF_AC97_REG_UNSUPPORTED ; 
 unsigned short AZF_REG_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned short,unsigned short) ; 
 unsigned short snd_azf3328_mixer_ac97_map_reg_idx (unsigned short) ; 
 int /*<<< orphan*/  snd_azf3328_mixer_ac97_map_unsupported (struct snd_azf3328 const*,unsigned short,char*) ; 
 int /*<<< orphan*/  snd_azf3328_mixer_outw (struct snd_azf3328 const*,unsigned short,unsigned short) ; 

__attribute__((used)) static void
snd_azf3328_mixer_ac97_write(struct snd_ac97 *ac97,
		     unsigned short reg_ac97, unsigned short val)
{
	const struct snd_azf3328 *chip = ac97->private_data;
	unsigned short reg_azf = snd_azf3328_mixer_ac97_map_reg_idx(reg_ac97);
	bool unsupported = false;

	dev_dbg(chip->card->dev,
		"snd_azf3328_mixer_ac97_write reg_ac97 %u val %u\n",
		reg_ac97, val);
	if (reg_azf & AZF_AC97_REG_UNSUPPORTED)
		unsupported = true;
	else {
		if (reg_azf & AZF_AC97_REG_REAL_IO_WRITE)
			snd_azf3328_mixer_outw(
				chip,
				reg_azf & AZF_REG_MASK,
				val
			);
		else
		if (reg_azf & AZF_AC97_REG_EMU_IO_WRITE) {
			switch (reg_ac97) {
			case AC97_REC_GAIN_MIC:
			case AC97_POWERDOWN:
			case AC97_EXTENDED_STATUS:
				/*
				 * Silently swallow these writes.
				 * Since for most registers our card doesn't
				 * actually support a comparable feature,
				 * this is exactly what we should do here.
				 * The AC97 layer's I/O caching probably
				 * automatically takes care of all the rest...
				 * (remembers written values etc.)
				 */
				break;
			default:
				unsupported = true;
				break;
			}
		}
	}
	if (unsupported)
		snd_azf3328_mixer_ac97_map_unsupported(chip, reg_ac97, "write");
}