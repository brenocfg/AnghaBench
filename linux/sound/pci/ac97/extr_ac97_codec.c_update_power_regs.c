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
struct snd_ac97 {int scaps; unsigned int power_up; int* regs; } ;
struct TYPE_2__ {unsigned int mask; size_t power_reg; } ;

/* Variables and functions */
 int AC97_PD_PR2 ; 
 int AC97_PD_PR3 ; 
 size_t AC97_POWERDOWN ; 
 int AC97_SCAP_CENTER_LFE_DAC ; 
 int AC97_SCAP_SURROUND_DAC ; 
 int PWIDX_ADC ; 
 int PWIDX_CLFE ; 
 int PWIDX_FRONT ; 
 int PWIDX_MIC ; 
 int PWIDX_SIZE ; 
 int PWIDX_SURR ; 
 scalar_t__ ac97_is_power_save_mode (struct snd_ac97*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_1__* power_regs ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,size_t,int,int) ; 

__attribute__((used)) static void update_power_regs(struct snd_ac97 *ac97)
{
	unsigned int power_up, bits;
	int i;

	power_up = (1 << PWIDX_FRONT) | (1 << PWIDX_ADC);
	power_up |= (1 << PWIDX_MIC);
	if (ac97->scaps & AC97_SCAP_SURROUND_DAC)
		power_up |= (1 << PWIDX_SURR);
	if (ac97->scaps & AC97_SCAP_CENTER_LFE_DAC)
		power_up |= (1 << PWIDX_CLFE);
#ifdef CONFIG_SND_AC97_POWER_SAVE
	if (ac97_is_power_save_mode(ac97))
		power_up = ac97->power_up;
#endif
	if (power_up) {
		if (ac97->regs[AC97_POWERDOWN] & AC97_PD_PR2) {
			/* needs power-up analog mix and vref */
			snd_ac97_update_bits(ac97, AC97_POWERDOWN,
					     AC97_PD_PR3, 0);
			msleep(1);
			snd_ac97_update_bits(ac97, AC97_POWERDOWN,
					     AC97_PD_PR2, 0);
		}
	}
	for (i = 0; i < PWIDX_SIZE; i++) {
		if (power_up & (1 << i))
			bits = 0;
		else
			bits = power_regs[i].mask;
		snd_ac97_update_bits(ac97, power_regs[i].power_reg,
				     power_regs[i].mask, bits);
	}
	if (! power_up) {
		if (! (ac97->regs[AC97_POWERDOWN] & AC97_PD_PR2)) {
			/* power down analog mix and vref */
			snd_ac97_update_bits(ac97, AC97_POWERDOWN,
					     AC97_PD_PR2, AC97_PD_PR2);
			snd_ac97_update_bits(ac97, AC97_POWERDOWN,
					     AC97_PD_PR3, AC97_PD_PR3);
		}
	}
}