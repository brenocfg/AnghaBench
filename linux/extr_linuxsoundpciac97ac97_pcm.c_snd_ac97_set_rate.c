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
struct snd_ac97 {int flags; int* regs; int scaps; int ext_id; TYPE_1__* bus; } ;
struct TYPE_2__ {unsigned int clock; } ;

/* Variables and functions */
 int AC97_DOUBLE_RATE ; 
 int /*<<< orphan*/  AC97_EA_DRA ; 
 int AC97_EA_VRA ; 
 int AC97_EA_VRM ; 
 int AC97_EI_DRA ; 
 size_t AC97_EXTENDED_STATUS ; 
 int AC97_GENERAL_PURPOSE ; 
 int /*<<< orphan*/  AC97_GP_DRSS_78 ; 
 int /*<<< orphan*/  AC97_GP_DRSS_MASK ; 
#define  AC97_PCM_FRONT_DAC_RATE 133 
#define  AC97_PCM_LFE_DAC_RATE 132 
#define  AC97_PCM_LR_ADC_RATE 131 
#define  AC97_PCM_MIC_ADC_RATE 130 
#define  AC97_PCM_SURR_DAC_RATE 129 
 int AC97_SCAP_CENTER_LFE_DAC ; 
 int AC97_SCAP_SURROUND_DAC ; 
#define  AC97_SPDIF 128 
 int EINVAL ; 
 int set_spdif_rate (struct snd_ac97*,unsigned int) ; 
 int /*<<< orphan*/  snd_ac97_read (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_update (struct snd_ac97*,int,unsigned int) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_update_power (struct snd_ac97*,int,int) ; 

int snd_ac97_set_rate(struct snd_ac97 *ac97, int reg, unsigned int rate)
{
	int dbl;
	unsigned int tmp;
	
	dbl = rate > 48000;
	if (dbl) {
		if (!(ac97->flags & AC97_DOUBLE_RATE))
			return -EINVAL;
		if (reg != AC97_PCM_FRONT_DAC_RATE)
			return -EINVAL;
	}

	snd_ac97_update_power(ac97, reg, 1);
	switch (reg) {
	case AC97_PCM_MIC_ADC_RATE:
		if ((ac97->regs[AC97_EXTENDED_STATUS] & AC97_EA_VRM) == 0)	/* MIC VRA */
			if (rate != 48000)
				return -EINVAL;
		break;
	case AC97_PCM_FRONT_DAC_RATE:
	case AC97_PCM_LR_ADC_RATE:
		if ((ac97->regs[AC97_EXTENDED_STATUS] & AC97_EA_VRA) == 0)	/* VRA */
			if (rate != 48000 && rate != 96000)
				return -EINVAL;
		break;
	case AC97_PCM_SURR_DAC_RATE:
		if (! (ac97->scaps & AC97_SCAP_SURROUND_DAC))
			return -EINVAL;
		break;
	case AC97_PCM_LFE_DAC_RATE:
		if (! (ac97->scaps & AC97_SCAP_CENTER_LFE_DAC))
			return -EINVAL;
		break;
	case AC97_SPDIF:
		/* special case */
		return set_spdif_rate(ac97, rate);
	default:
		return -EINVAL;
	}
	if (dbl)
		rate /= 2;
	tmp = (rate * ac97->bus->clock) / 48000;
	if (tmp > 65535)
		return -EINVAL;
	if ((ac97->ext_id & AC97_EI_DRA) && reg == AC97_PCM_FRONT_DAC_RATE)
		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_DRA, dbl ? AC97_EA_DRA : 0);
	snd_ac97_update(ac97, reg, tmp & 0xffff);
	snd_ac97_read(ac97, reg);
	if ((ac97->ext_id & AC97_EI_DRA) && reg == AC97_PCM_FRONT_DAC_RATE) {
		/* Intel controllers require double rate data to be put in
		 * slots 7+8
		 */
		snd_ac97_update_bits(ac97, AC97_GENERAL_PURPOSE,
				     AC97_GP_DRSS_MASK,
				     dbl ? AC97_GP_DRSS_78 : 0);
		snd_ac97_read(ac97, AC97_GENERAL_PURPOSE);
	}
	return 0;
}