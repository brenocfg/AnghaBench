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
struct snd_ac97 {int ext_id; int /*<<< orphan*/  flags; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 unsigned short AC97_AD198X_AC97NC ; 
 unsigned short AC97_AD198X_HPSEL ; 
 unsigned short AC97_AD198X_LOSEL ; 
 unsigned short AC97_AD198X_MSPLT ; 
 int /*<<< orphan*/  AC97_AD_MISC ; 
 int AC97_EI_REV_23 ; 
 int AC97_EI_REV_MASK ; 
 int /*<<< orphan*/  AC97_STEREO_MUTES ; 
 int /*<<< orphan*/  ad1985_update_jacks (struct snd_ac97*) ; 
 int /*<<< orphan*/  patch_ad1881 (struct snd_ac97*) ; 
 int /*<<< orphan*/  patch_ad1985_build_ops ; 
 unsigned short snd_ac97_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int patch_ad1985(struct snd_ac97 * ac97)
{
	unsigned short misc;
	
	patch_ad1881(ac97);
	ac97->build_ops = &patch_ad1985_build_ops;
	misc = snd_ac97_read(ac97, AC97_AD_MISC);
	/* switch front/surround line-out/hp-out */
	/* AD-compatible mode */
	/* Stereo mutes enabled */
	snd_ac97_write_cache(ac97, AC97_AD_MISC, misc |
			     AC97_AD198X_LOSEL |
			     AC97_AD198X_HPSEL |
			     AC97_AD198X_MSPLT |
			     AC97_AD198X_AC97NC);
	ac97->flags |= AC97_STEREO_MUTES;

	/* update current jack configuration */
	ad1985_update_jacks(ac97);

	/* on AD1985 rev. 3, AC'97 revision bits are zero */
	ac97->ext_id = (ac97->ext_id & ~AC97_EI_REV_MASK) | AC97_EI_REV_23;
	return 0;
}