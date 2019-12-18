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
struct twl4030_priv {int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_bits; int /*<<< orphan*/  rate; struct snd_pcm_substream* master_substream; struct snd_pcm_substream* slave_substream; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl4030_constraints(struct twl4030_priv *twl4030,
				struct snd_pcm_substream *mst_substream)
{
	struct snd_pcm_substream *slv_substream;

	/* Pick the stream, which need to be constrained */
	if (mst_substream == twl4030->master_substream)
		slv_substream = twl4030->slave_substream;
	else if (mst_substream == twl4030->slave_substream)
		slv_substream = twl4030->master_substream;
	else /* This should not happen.. */
		return;

	/* Set the constraints according to the already configured stream */
	snd_pcm_hw_constraint_single(slv_substream->runtime,
				SNDRV_PCM_HW_PARAM_RATE,
				twl4030->rate);

	snd_pcm_hw_constraint_single(slv_substream->runtime,
				SNDRV_PCM_HW_PARAM_SAMPLE_BITS,
				twl4030->sample_bits);

	snd_pcm_hw_constraint_single(slv_substream->runtime,
				SNDRV_PCM_HW_PARAM_CHANNELS,
				twl4030->channels);
}