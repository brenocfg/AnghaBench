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
struct snd_ac97 {int ext_id; int flags; scalar_t__ id; unsigned int spdif_status; int /*<<< orphan*/  reg_mutex; } ;

/* Variables and functions */
 unsigned short AC97_CSR_SPDIF ; 
 int AC97_CS_SPDIF ; 
 unsigned short AC97_EA_SPDIF ; 
 int AC97_EI_SPDIF ; 
 unsigned short AC97_EXTENDED_STATUS ; 
 scalar_t__ AC97_ID_CM9739 ; 
 unsigned short AC97_SC_SPSR_32K ; 
 unsigned short AC97_SC_SPSR_44K ; 
 unsigned short AC97_SC_SPSR_48K ; 
 unsigned short AC97_SC_SPSR_MASK ; 
 int AC97_SC_SPSR_SHIFT ; 
 unsigned short AC97_SPDIF ; 
 int EINVAL ; 
 int ENODEV ; 
 unsigned int IEC958_AES0_PROFESSIONAL ; 
 unsigned int IEC958_AES0_PRO_FS ; 
 unsigned int IEC958_AES0_PRO_FS_32000 ; 
 unsigned int IEC958_AES0_PRO_FS_44100 ; 
 unsigned int IEC958_AES0_PRO_FS_48000 ; 
 int IEC958_AES3_CON_FS ; 
 int IEC958_AES3_CON_FS_32000 ; 
 int IEC958_AES3_CON_FS_44100 ; 
 int IEC958_AES3_CON_FS_48000 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned short snd_ac97_read (struct snd_ac97*,unsigned short) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,unsigned short,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_update_bits_nolock (struct snd_ac97*,unsigned short,unsigned short,unsigned short) ; 

__attribute__((used)) static int set_spdif_rate(struct snd_ac97 *ac97, unsigned short rate)
{
	unsigned short old, bits, reg, mask;
	unsigned int sbits;

	if (! (ac97->ext_id & AC97_EI_SPDIF))
		return -ENODEV;

	/* TODO: double rate support */
	if (ac97->flags & AC97_CS_SPDIF) {
		switch (rate) {
		case 48000: bits = 0; break;
		case 44100: bits = 1 << AC97_SC_SPSR_SHIFT; break;
		default: /* invalid - disable output */
			snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
			return -EINVAL;
		}
		reg = AC97_CSR_SPDIF;
		mask = 1 << AC97_SC_SPSR_SHIFT;
	} else {
		if (ac97->id == AC97_ID_CM9739 && rate != 48000) {
			snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
			return -EINVAL;
		}
		switch (rate) {
		case 44100: bits = AC97_SC_SPSR_44K; break;
		case 48000: bits = AC97_SC_SPSR_48K; break;
		case 32000: bits = AC97_SC_SPSR_32K; break;
		default: /* invalid - disable output */
			snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
			return -EINVAL;
		}
		reg = AC97_SPDIF;
		mask = AC97_SC_SPSR_MASK;
	}

	mutex_lock(&ac97->reg_mutex);
	old = snd_ac97_read(ac97, reg) & mask;
	if (old != bits) {
		snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, 0);
		snd_ac97_update_bits_nolock(ac97, reg, mask, bits);
		/* update the internal spdif bits */
		sbits = ac97->spdif_status;
		if (sbits & IEC958_AES0_PROFESSIONAL) {
			sbits &= ~IEC958_AES0_PRO_FS;
			switch (rate) {
			case 44100: sbits |= IEC958_AES0_PRO_FS_44100; break;
			case 48000: sbits |= IEC958_AES0_PRO_FS_48000; break;
			case 32000: sbits |= IEC958_AES0_PRO_FS_32000; break;
			}
		} else {
			sbits &= ~(IEC958_AES3_CON_FS << 24);
			switch (rate) {
			case 44100: sbits |= IEC958_AES3_CON_FS_44100<<24; break;
			case 48000: sbits |= IEC958_AES3_CON_FS_48000<<24; break;
			case 32000: sbits |= IEC958_AES3_CON_FS_32000<<24; break;
			}
		}
		ac97->spdif_status = sbits;
	}
	snd_ac97_update_bits_nolock(ac97, AC97_EXTENDED_STATUS, AC97_EA_SPDIF, AC97_EA_SPDIF);
	mutex_unlock(&ac97->reg_mutex);
	return 0;
}