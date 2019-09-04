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
#define  AC97_SC_SPSR_32K 133 
#define  AC97_SC_SPSR_44K 132 
#define  AC97_SC_SPSR_48K 131 
 unsigned short AC97_SC_SPSR_MASK ; 
 int /*<<< orphan*/  AC97_SPDIF ; 
 scalar_t__ ARRAY_SIZE (unsigned short*) ; 
#define  SNDRV_PCM_RATE_32000 130 
#define  SNDRV_PCM_RATE_44100 129 
#define  SNDRV_PCM_RATE_48000 128 
 unsigned short snd_ac97_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,unsigned short,unsigned short) ; 

__attribute__((used)) static unsigned int snd_ac97_determine_spdif_rates(struct snd_ac97 *ac97)
{
	unsigned int result = 0;
	int i;
	static unsigned short ctl_bits[] = {
		AC97_SC_SPSR_44K, AC97_SC_SPSR_32K, AC97_SC_SPSR_48K
	};
	static unsigned int rate_bits[] = {
		SNDRV_PCM_RATE_44100, SNDRV_PCM_RATE_32000, SNDRV_PCM_RATE_48000
	};

	for (i = 0; i < (int)ARRAY_SIZE(ctl_bits); i++) {
		snd_ac97_update_bits(ac97, AC97_SPDIF, AC97_SC_SPSR_MASK, ctl_bits[i]);
		if ((snd_ac97_read(ac97, AC97_SPDIF) & AC97_SC_SPSR_MASK) == ctl_bits[i])
			result |= rate_bits[i];
	}
	return result;
}