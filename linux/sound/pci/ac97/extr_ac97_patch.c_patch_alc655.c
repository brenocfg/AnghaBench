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
struct TYPE_2__ {int dev_flags; } ;
struct snd_ac97 {scalar_t__ id; int subsystem_vendor; int subsystem_device; int /*<<< orphan*/  ext_id; TYPE_1__ spec; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int AC97_ALC650_LFE_DAC_VOL ; 
 int AC97_ALC650_MULTICH ; 
 int AC97_ALC650_REVISION ; 
 int AC97_ALC650_SURR_DAC_VOL ; 
 int /*<<< orphan*/  AC97_EI_SPDIF ; 
 scalar_t__ AC97_ID_ALC658 ; 
 scalar_t__ AC97_ID_ALC658D ; 
 int AC97_INT_PAGING ; 
 int AC97_PAGE_MASK ; 
 int AC97_PAGE_VENDOR ; 
 int /*<<< orphan*/  patch_alc655_ops ; 
 int snd_ac97_read (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int,int,int) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int,int) ; 

__attribute__((used)) static int patch_alc655(struct snd_ac97 * ac97)
{
	unsigned int val;

	if (ac97->id == AC97_ID_ALC658) {
		ac97->spec.dev_flags = 1; /* ALC658 */
		if ((snd_ac97_read(ac97, AC97_ALC650_REVISION) & 0x3f) == 2) {
			ac97->id = AC97_ID_ALC658D;
			ac97->spec.dev_flags = 2;
		}
	}

	ac97->build_ops = &patch_alc655_ops;

	/* assume only page 0 for writing cache */
	snd_ac97_update_bits(ac97, AC97_INT_PAGING, AC97_PAGE_MASK, AC97_PAGE_VENDOR);

	/* adjust default values */
	val = snd_ac97_read(ac97, 0x7a); /* misc control */
	if (ac97->spec.dev_flags) /* ALC658 */
		val &= ~(1 << 1); /* Pin 47 is spdif input pin */
	else { /* ALC655 */
		if (ac97->subsystem_vendor == 0x1462 &&
		    (ac97->subsystem_device == 0x0131 || /* MSI S270 laptop */
		     ac97->subsystem_device == 0x0161 || /* LG K1 Express */
		     ac97->subsystem_device == 0x0351 || /* MSI L725 laptop */
		     ac97->subsystem_device == 0x0471 || /* MSI L720 laptop */
		     ac97->subsystem_device == 0x0061))  /* MSI S250 laptop */
			val &= ~(1 << 1); /* Pin 47 is EAPD (for internal speaker) */
		else
			val |= (1 << 1); /* Pin 47 is spdif input pin */
		/* this seems missing on some hardwares */
		ac97->ext_id |= AC97_EI_SPDIF;
	}
	val &= ~(1 << 12); /* vref enable */
	snd_ac97_write_cache(ac97, 0x7a, val);
	/* set default: spdif-in enabled,
	   spdif-in monitor off, spdif-in PCM off
	   center on mic off, surround on line-in off
	   duplicate front off
	*/
	snd_ac97_write_cache(ac97, AC97_ALC650_MULTICH, 1<<15);

	/* full DAC volume */
	snd_ac97_write_cache(ac97, AC97_ALC650_SURR_DAC_VOL, 0x0808);
	snd_ac97_write_cache(ac97, AC97_ALC650_LFE_DAC_VOL, 0x0808);

	/* update undocumented bit... */
	if (ac97->id == AC97_ID_ALC658D)
		snd_ac97_update_bits(ac97, 0x74, 0x0800, 0x0800);

	return 0;
}