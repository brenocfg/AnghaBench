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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dummy; } ;
struct snd_pcm_hw_constraint_list {unsigned int* list; int count; scalar_t__ mask; } ;
struct rsnd_dai_stream {int dummy; } ;
struct rsnd_dai {int /*<<< orphan*/  capture; int /*<<< orphan*/  playback; struct snd_pcm_hw_constraint_list constraint; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  rsnd_dai_stream_init (struct rsnd_dai_stream*,struct snd_pcm_substream*) ; 
 struct rsnd_dai* rsnd_dai_to_rdai (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  rsnd_pcm_hardware ; 
 unsigned int rsnd_rdai_channels_get (struct rsnd_dai*) ; 
 scalar_t__ rsnd_rdai_is_clk_master (struct rsnd_dai*) ; 
 struct rsnd_dai_stream* rsnd_rdai_to_io (struct rsnd_dai*,struct snd_pcm_substream*) ; 
 unsigned int* rsnd_soc_hw_channels_list ; 
 int /*<<< orphan*/  rsnd_soc_hw_rule_channels ; 
 int /*<<< orphan*/  rsnd_soc_hw_rule_rate ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm_hw_constraint_list*) ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsnd_soc_dai_startup(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct rsnd_dai *rdai = rsnd_dai_to_rdai(dai);
	struct rsnd_dai_stream *io = rsnd_rdai_to_io(rdai, substream);
	struct snd_pcm_hw_constraint_list *constraint = &rdai->constraint;
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned int max_channels = rsnd_rdai_channels_get(rdai);
	int i;

	rsnd_dai_stream_init(io, substream);

	/*
	 * Channel Limitation
	 * It depends on Platform design
	 */
	constraint->list	= rsnd_soc_hw_channels_list;
	constraint->count	= 0;
	constraint->mask	= 0;

	for (i = 0; i < ARRAY_SIZE(rsnd_soc_hw_channels_list); i++) {
		if (rsnd_soc_hw_channels_list[i] > max_channels)
			break;
		constraint->count = i + 1;
	}

	snd_soc_set_runtime_hwparams(substream, &rsnd_pcm_hardware);

	snd_pcm_hw_constraint_list(runtime, 0,
				   SNDRV_PCM_HW_PARAM_CHANNELS, constraint);

	snd_pcm_hw_constraint_integer(runtime,
				      SNDRV_PCM_HW_PARAM_PERIODS);

	/*
	 * Sampling Rate / Channel Limitation
	 * It depends on Clock Master Mode
	 */
	if (rsnd_rdai_is_clk_master(rdai)) {
		int is_play = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

		snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				    rsnd_soc_hw_rule_rate,
				    is_play ? &rdai->playback : &rdai->capture,
				    SNDRV_PCM_HW_PARAM_CHANNELS, -1);
		snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				    rsnd_soc_hw_rule_channels,
				    is_play ? &rdai->playback : &rdai->capture,
				    SNDRV_PCM_HW_PARAM_RATE, -1);
	}

	return 0;
}