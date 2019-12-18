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
struct snd_pcm_runtime {int dummy; } ;
struct snd_pcm_hw_constraint_list {unsigned int const* list; int count; scalar_t__ mask; } ;
struct ak4613_priv {unsigned int const sysclk; struct snd_pcm_hw_constraint_list constraint; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int const*) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm_hw_constraint_list*) ; 

__attribute__((used)) static void ak4613_hw_constraints(struct ak4613_priv *priv,
				  struct snd_pcm_runtime *runtime)
{
	static const unsigned int ak4613_rates[] = {
		 32000,
		 44100,
		 48000,
		 64000,
		 88200,
		 96000,
		176400,
		192000,
	};
	struct snd_pcm_hw_constraint_list *constraint = &priv->constraint;
	unsigned int fs;
	int i;

	constraint->list	= ak4613_rates;
	constraint->mask	= 0;
	constraint->count	= 0;

	/*
	 * Slave Mode
	 *	Normal: [32kHz, 48kHz] : 256fs,384fs or 512fs
	 *	Double: [64kHz, 96kHz] : 256fs
	 *	Quad  : [128kHz,192kHz]: 128fs
	 *
	 * Master mode
	 *	Normal: [32kHz, 48kHz] : 256fs or 512fs
	 *	Double: [64kHz, 96kHz] : 256fs
	 *	Quad  : [128kHz,192kHz]: 128fs
	*/
	for (i = 0; i < ARRAY_SIZE(ak4613_rates); i++) {
		/* minimum fs on each range */
		fs = (ak4613_rates[i] <= 96000) ? 256 : 128;

		if (priv->sysclk >= ak4613_rates[i] * fs)
			constraint->count = i + 1;
	}

	snd_pcm_hw_constraint_list(runtime, 0,
				SNDRV_PCM_HW_PARAM_RATE, constraint);
}