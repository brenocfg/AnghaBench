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
struct TYPE_2__ {int /*<<< orphan*/ * p; } ;
struct snd_kcontrol {TYPE_1__ tlv; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  slave_sws_vt1616 ; 
 int /*<<< orphan*/  slave_vols_vt1616 ; 
 int snd_ac97_add_vmaster (struct snd_ac97*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * snd_ac97_controls_vt1616 ; 
 struct snd_kcontrol* snd_ac97_find_mixer_ctl (struct snd_ac97*,char*) ; 
 int /*<<< orphan*/  snd_ac97_rename_vol_ctl (struct snd_ac97*,char*,char*) ; 
 scalar_t__ snd_ac97_try_bit (struct snd_ac97*,int,int) ; 

__attribute__((used)) static int patch_vt1616_specific(struct snd_ac97 * ac97)
{
	struct snd_kcontrol *kctl;
	int err;

	if (snd_ac97_try_bit(ac97, 0x5a, 9))
		if ((err = patch_build_controls(ac97, &snd_ac97_controls_vt1616[0], 1)) < 0)
			return err;
	if ((err = patch_build_controls(ac97, &snd_ac97_controls_vt1616[1], ARRAY_SIZE(snd_ac97_controls_vt1616) - 1)) < 0)
		return err;

	/* There is already a misnamed master switch.  Rename it.  */
	kctl = snd_ac97_find_mixer_ctl(ac97, "Master Playback Volume");
	if (!kctl)
		return -EINVAL;

	snd_ac97_rename_vol_ctl(ac97, "Master Playback", "Front Playback");

	err = snd_ac97_add_vmaster(ac97, "Master Playback Volume",
				   kctl->tlv.p, slave_vols_vt1616);
	if (err < 0)
		return err;

	err = snd_ac97_add_vmaster(ac97, "Master Playback Switch",
				   NULL, slave_sws_vt1616);
	if (err < 0)
		return err;

	return 0;
}