#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lo_as_master; } ;
struct TYPE_3__ {TYPE_2__ ad18xx; } ;
struct snd_ac97 {int subsystem_vendor; int subsystem_device; int /*<<< orphan*/  flags; TYPE_1__ spec; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 unsigned short AC97_AD198X_AC97NC ; 
 unsigned short AC97_AD198X_HPSEL ; 
 unsigned short AC97_AD198X_LOSEL ; 
 unsigned short AC97_AD198X_MSPLT ; 
 int /*<<< orphan*/  AC97_AD_MISC ; 
 int /*<<< orphan*/  AC97_STEREO_MUTES ; 
 int /*<<< orphan*/  patch_ad1881 (struct snd_ac97*) ; 
 int /*<<< orphan*/  patch_ad1888_build_ops ; 
 unsigned short snd_ac97_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int patch_ad1888(struct snd_ac97 * ac97)
{
	unsigned short misc;
	
	patch_ad1881(ac97);
	ac97->build_ops = &patch_ad1888_build_ops;

	/*
	 * LO can be used as a real line-out on some devices,
	 * and we need to revert the front/surround mixer switches
	 */
	if (ac97->subsystem_vendor == 0x1043 &&
	    ac97->subsystem_device == 0x1193) /* ASUS A9T laptop */
		ac97->spec.ad18xx.lo_as_master = 1;

	misc = snd_ac97_read(ac97, AC97_AD_MISC);
	/* AD-compatible mode */
	/* Stereo mutes enabled */
	misc |= AC97_AD198X_MSPLT | AC97_AD198X_AC97NC;
	if (!ac97->spec.ad18xx.lo_as_master)
		/* Switch FRONT/SURROUND LINE-OUT/HP-OUT default connection */
		/* it seems that most vendors connect line-out connector to
		 * headphone out of AC'97
		 */
		misc |= AC97_AD198X_LOSEL | AC97_AD198X_HPSEL;

	snd_ac97_write_cache(ac97, AC97_AD_MISC, misc);
	ac97->flags |= AC97_STEREO_MUTES;
	return 0;
}