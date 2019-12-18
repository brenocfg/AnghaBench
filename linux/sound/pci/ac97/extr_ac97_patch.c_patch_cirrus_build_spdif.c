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
struct snd_ac97 {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CSR_SPDIF ; 
#define  AC97_ID_CS4205 128 
 int AC97_ID_CS_MASK ; 
 int patch_build_controls (struct snd_ac97*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * snd_ac97_cirrus_controls_spdif ; 
 int /*<<< orphan*/ * snd_ac97_controls_spdif ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int patch_cirrus_build_spdif(struct snd_ac97 * ac97)
{
	int err;

	/* con mask, pro mask, default */
	if ((err = patch_build_controls(ac97, &snd_ac97_controls_spdif[0], 3)) < 0)
		return err;
	/* switch, spsa */
	if ((err = patch_build_controls(ac97, &snd_ac97_cirrus_controls_spdif[0], 1)) < 0)
		return err;
	switch (ac97->id & AC97_ID_CS_MASK) {
	case AC97_ID_CS4205:
		if ((err = patch_build_controls(ac97, &snd_ac97_cirrus_controls_spdif[1], 1)) < 0)
			return err;
		break;
	}
	/* set default PCM S/PDIF params */
	/* consumer,PCM audio,no copyright,no preemphasis,PCM coder,original,48000Hz */
	snd_ac97_write_cache(ac97, AC97_CSR_SPDIF, 0x0a20);
	return 0;
}