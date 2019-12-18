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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int patch_sigmatel_stac97xx_specific (struct snd_ac97*) ; 
 int /*<<< orphan*/  snd_ac97_rename_vol_ctl (struct snd_ac97*,char*,char*) ; 
 int /*<<< orphan*/  snd_ac97_sigmatel_stac9758_controls ; 

__attribute__((used)) static int patch_sigmatel_stac9758_specific(struct snd_ac97 *ac97)
{
	int err;

	err = patch_sigmatel_stac97xx_specific(ac97);
	if (err < 0)
		return err;
	err = patch_build_controls(ac97, snd_ac97_sigmatel_stac9758_controls,
				   ARRAY_SIZE(snd_ac97_sigmatel_stac9758_controls));
	if (err < 0)
		return err;
	/* DAC-A direct */
	snd_ac97_rename_vol_ctl(ac97, "Headphone Playback", "Front Playback");
	/* DAC-A to Mix = PCM */
	/* DAC-B direct = Surround */
	/* DAC-B to Mix */
	snd_ac97_rename_vol_ctl(ac97, "Video Playback", "Surround Mix Playback");
	/* DAC-C direct = Center/LFE */

	return 0;
}