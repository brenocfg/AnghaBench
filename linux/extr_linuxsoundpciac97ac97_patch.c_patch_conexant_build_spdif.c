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
 int /*<<< orphan*/  AC97_CXR_AUDIO_MISC ; 
 int AC97_CXR_COPYRGT ; 
 int AC97_CXR_SPDIFEN ; 
 int AC97_CXR_SPDIF_MASK ; 
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * snd_ac97_conexant_controls_spdif ; 
 int /*<<< orphan*/ * snd_ac97_controls_spdif ; 
 int snd_ac97_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int patch_conexant_build_spdif(struct snd_ac97 * ac97)
{
	int err;

	/* con mask, pro mask, default */
	if ((err = patch_build_controls(ac97, &snd_ac97_controls_spdif[0], 3)) < 0)
		return err;
	/* switch */
	if ((err = patch_build_controls(ac97, &snd_ac97_conexant_controls_spdif[0], 1)) < 0)
		return err;
	/* set default PCM S/PDIF params */
	/* consumer,PCM audio,no copyright,no preemphasis,PCM coder,original,48000Hz */
	snd_ac97_write_cache(ac97, AC97_CXR_AUDIO_MISC,
			     snd_ac97_read(ac97, AC97_CXR_AUDIO_MISC) & ~(AC97_CXR_SPDIFEN|AC97_CXR_COPYRGT|AC97_CXR_SPDIF_MASK));
	return 0;
}