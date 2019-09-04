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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_azf3328_codec_data* private_data; int /*<<< orphan*/  hw; } ;
struct snd_azf3328_codec_data {struct snd_pcm_substream* substream; } ;
struct snd_azf3328 {struct snd_azf3328_codec_data* codecs; } ;
typedef  enum snd_azf3328_codec_type { ____Placeholder_snd_azf3328_codec_type } snd_azf3328_codec_type ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  snd_azf3328_hardware ; 
 int /*<<< orphan*/  snd_azf3328_hw_constraints_rates ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct snd_azf3328* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int
snd_azf3328_pcm_open(struct snd_pcm_substream *substream,
		     enum snd_azf3328_codec_type codec_type
)
{
	struct snd_azf3328 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_azf3328_codec_data *codec = &chip->codecs[codec_type];

	codec->substream = substream;

	/* same parameters for all our codecs - at least we think so... */
	runtime->hw = snd_azf3328_hardware;

	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &snd_azf3328_hw_constraints_rates);
	runtime->private_data = codec;
	return 0;
}