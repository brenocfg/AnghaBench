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
struct snd_kcontrol {void* private_value; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_3D_CONTROL ; 
 void* AC97_SINGLE_VALUE (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ac97_find_mixer_ctl (struct snd_ac97*,char*) ; 
 int /*<<< orphan*/  snd_ac97_rename_vol_ctl (struct snd_ac97*,char*,char*) ; 

__attribute__((used)) static int patch_aztech_azf3328_specific(struct snd_ac97 *ac97)
{
	struct snd_kcontrol *kctl_3d_center =
		snd_ac97_find_mixer_ctl(ac97, "3D Control - Center");
	struct snd_kcontrol *kctl_3d_depth =
		snd_ac97_find_mixer_ctl(ac97, "3D Control - Depth");

	/*
	 * 3D register is different from AC97 standard layout
	 * (also do some renaming, to resemble Windows driver naming)
	 */
	if (kctl_3d_center) {
		kctl_3d_center->private_value =
			AC97_SINGLE_VALUE(AC97_3D_CONTROL, 1, 0x07, 0);
		snd_ac97_rename_vol_ctl(ac97,
			"3D Control - Center", "3D Control - Width"
		);
	}
	if (kctl_3d_depth)
		kctl_3d_depth->private_value =
			AC97_SINGLE_VALUE(AC97_3D_CONTROL, 8, 0x03, 0);

	/* Aztech Windows driver calls the
	   equivalent control "Modem Playback", thus rename it: */
	snd_ac97_rename_vol_ctl(ac97,
		"Master Mono Playback", "Modem Playback"
	);
	snd_ac97_rename_vol_ctl(ac97,
		"Headphone Playback", "FM Synth Playback"
	);

	return 0;
}