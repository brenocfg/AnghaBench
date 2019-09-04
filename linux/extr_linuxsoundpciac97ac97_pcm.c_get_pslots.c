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
typedef  int u16 ;
struct snd_ac97 {int addr; int scaps; int ext_id; int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EI_DACS_SLOT_MASK ; 
 int AC97_EI_DACS_SLOT_SHIFT ; 
 int AC97_EI_SPDIF ; 
 size_t AC97_EXTENDED_ID ; 
 int AC97_SCAP_CENTER_LFE_DAC ; 
 int AC97_SCAP_SURROUND_DAC ; 
 int AC97_SLOT_LFE ; 
 int AC97_SLOT_PCM_CENTER ; 
 int AC97_SLOT_PCM_LEFT ; 
 int AC97_SLOT_PCM_RIGHT ; 
 int AC97_SLOT_PCM_SLEFT ; 
 int AC97_SLOT_PCM_SRIGHT ; 
 int AC97_SLOT_SPDIF_LEFT ; 
 int AC97_SLOT_SPDIF_LEFT1 ; 
 int AC97_SLOT_SPDIF_LEFT2 ; 
 int AC97_SLOT_SPDIF_RIGHT ; 
 int AC97_SLOT_SPDIF_RIGHT1 ; 
 int AC97_SLOT_SPDIF_RIGHT2 ; 
 scalar_t__ ac97_can_amap (struct snd_ac97*) ; 
 int /*<<< orphan*/  ac97_is_audio (struct snd_ac97*) ; 
 scalar_t__ ac97_is_rev22 (struct snd_ac97*) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,size_t,int) ; 

__attribute__((used)) static unsigned short get_pslots(struct snd_ac97 *ac97, unsigned char *rate_table, unsigned short *spdif_slots)
{
	if (!ac97_is_audio(ac97))
		return 0;
	if (ac97_is_rev22(ac97) || ac97_can_amap(ac97)) {
		unsigned short slots = 0;
		if (ac97_is_rev22(ac97)) {
			/* Note: it's simply emulation of AMAP behaviour */
			u16 es;
			es = ac97->regs[AC97_EXTENDED_ID] &= ~AC97_EI_DACS_SLOT_MASK;
			switch (ac97->addr) {
			case 1:
			case 2: es |= (1<<AC97_EI_DACS_SLOT_SHIFT); break;
			case 3: es |= (2<<AC97_EI_DACS_SLOT_SHIFT); break;
			}
			snd_ac97_write_cache(ac97, AC97_EXTENDED_ID, es);
		}
		switch (ac97->addr) {
		case 0:
			slots |= (1<<AC97_SLOT_PCM_LEFT)|(1<<AC97_SLOT_PCM_RIGHT);
			if (ac97->scaps & AC97_SCAP_SURROUND_DAC)
				slots |= (1<<AC97_SLOT_PCM_SLEFT)|(1<<AC97_SLOT_PCM_SRIGHT);
			if (ac97->scaps & AC97_SCAP_CENTER_LFE_DAC)
				slots |= (1<<AC97_SLOT_PCM_CENTER)|(1<<AC97_SLOT_LFE);
			if (ac97->ext_id & AC97_EI_SPDIF) {
				if (!(ac97->scaps & AC97_SCAP_SURROUND_DAC))
					*spdif_slots = (1<<AC97_SLOT_SPDIF_LEFT)|(1<<AC97_SLOT_SPDIF_RIGHT);
				else if (!(ac97->scaps & AC97_SCAP_CENTER_LFE_DAC))
					*spdif_slots = (1<<AC97_SLOT_SPDIF_LEFT1)|(1<<AC97_SLOT_SPDIF_RIGHT1);
				else
					*spdif_slots = (1<<AC97_SLOT_SPDIF_LEFT2)|(1<<AC97_SLOT_SPDIF_RIGHT2);
			}
			*rate_table = 0;
			break;
		case 1:
		case 2:
			slots |= (1<<AC97_SLOT_PCM_SLEFT)|(1<<AC97_SLOT_PCM_SRIGHT);
			if (ac97->scaps & AC97_SCAP_SURROUND_DAC)
				slots |= (1<<AC97_SLOT_PCM_CENTER)|(1<<AC97_SLOT_LFE);
			if (ac97->ext_id & AC97_EI_SPDIF) {
				if (!(ac97->scaps & AC97_SCAP_SURROUND_DAC))
					*spdif_slots = (1<<AC97_SLOT_SPDIF_LEFT1)|(1<<AC97_SLOT_SPDIF_RIGHT1);
				else
					*spdif_slots = (1<<AC97_SLOT_SPDIF_LEFT2)|(1<<AC97_SLOT_SPDIF_RIGHT2);
			}
			*rate_table = 1;
			break;
		case 3:
			slots |= (1<<AC97_SLOT_PCM_CENTER)|(1<<AC97_SLOT_LFE);
			if (ac97->ext_id & AC97_EI_SPDIF)
				*spdif_slots = (1<<AC97_SLOT_SPDIF_LEFT2)|(1<<AC97_SLOT_SPDIF_RIGHT2);
			*rate_table = 2;
			break;
		}
		return slots;
	} else {
		unsigned short slots;
		slots = (1<<AC97_SLOT_PCM_LEFT)|(1<<AC97_SLOT_PCM_RIGHT);
		if (ac97->scaps & AC97_SCAP_SURROUND_DAC)
			slots |= (1<<AC97_SLOT_PCM_SLEFT)|(1<<AC97_SLOT_PCM_SRIGHT);
		if (ac97->scaps & AC97_SCAP_CENTER_LFE_DAC)
			slots |= (1<<AC97_SLOT_PCM_CENTER)|(1<<AC97_SLOT_LFE);
		if (ac97->ext_id & AC97_EI_SPDIF) {
			if (!(ac97->scaps & AC97_SCAP_SURROUND_DAC))
				*spdif_slots = (1<<AC97_SLOT_SPDIF_LEFT)|(1<<AC97_SLOT_SPDIF_RIGHT);
			else if (!(ac97->scaps & AC97_SCAP_CENTER_LFE_DAC))
				*spdif_slots = (1<<AC97_SLOT_SPDIF_LEFT1)|(1<<AC97_SLOT_SPDIF_RIGHT1);
			else
				*spdif_slots = (1<<AC97_SLOT_SPDIF_LEFT2)|(1<<AC97_SLOT_SPDIF_RIGHT2);
		}
		*rate_table = 0;
		return slots;
	}
}