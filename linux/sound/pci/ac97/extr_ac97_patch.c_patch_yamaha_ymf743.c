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
struct snd_ac97 {int caps; int /*<<< orphan*/  ext_id; int /*<<< orphan*/ * rates; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int AC97_BC_BASS_TREBLE ; 
 int /*<<< orphan*/  AC97_EI_SPDIF ; 
 size_t AC97_RATES_SPDIF ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_48000 ; 
 int /*<<< orphan*/  patch_yamaha_ymf743_ops ; 

__attribute__((used)) static int patch_yamaha_ymf743(struct snd_ac97 *ac97)
{
	ac97->build_ops = &patch_yamaha_ymf743_ops;
	ac97->caps |= AC97_BC_BASS_TREBLE;
	ac97->caps |= 0x04 << 10; /* Yamaha 3D enhancement */
	ac97->rates[AC97_RATES_SPDIF] = SNDRV_PCM_RATE_48000; /* 48k only */
	ac97->ext_id |= AC97_EI_SPDIF; /* force the detection of spdif */
	return 0;
}