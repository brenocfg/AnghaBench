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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int format; int /*<<< orphan*/  channels; int /*<<< orphan*/  rate; scalar_t__ private_data; } ;
struct echoaudio {TYPE_1__* card; } ;
struct audiopipe {int index; } ;
struct audioformat {int data_are_bigendian; int bits_per_sample; scalar_t__ mono_to_stereo; int /*<<< orphan*/  interleave; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 132 
#define  SNDRV_PCM_FORMAT_S24_3LE 131 
#define  SNDRV_PCM_FORMAT_S32_BE 130 
#define  SNDRV_PCM_FORMAT_S32_LE 129 
#define  SNDRV_PCM_FORMAT_U8 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  is_pipe_allocated (struct echoaudio*,int) ; 
 int px_num (struct echoaudio*) ; 
 int /*<<< orphan*/  set_audio_format (struct echoaudio*,int,struct audioformat*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct echoaudio* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pcm_prepare(struct snd_pcm_substream *substream)
{
	struct echoaudio *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct audioformat format;
	int pipe_index = ((struct audiopipe *)runtime->private_data)->index;

	dev_dbg(chip->card->dev, "Prepare rate=%d format=%d channels=%d\n",
		runtime->rate, runtime->format, runtime->channels);
	format.interleave = runtime->channels;
	format.data_are_bigendian = 0;
	format.mono_to_stereo = 0;
	switch (runtime->format) {
	case SNDRV_PCM_FORMAT_U8:
		format.bits_per_sample = 8;
		break;
	case SNDRV_PCM_FORMAT_S16_LE:
		format.bits_per_sample = 16;
		break;
	case SNDRV_PCM_FORMAT_S24_3LE:
		format.bits_per_sample = 24;
		break;
	case SNDRV_PCM_FORMAT_S32_BE:
		format.data_are_bigendian = 1;
		/* fall through */
	case SNDRV_PCM_FORMAT_S32_LE:
		format.bits_per_sample = 32;
		break;
	default:
		dev_err(chip->card->dev,
			"Prepare error: unsupported format %d\n",
			runtime->format);
		return -EINVAL;
	}

	if (snd_BUG_ON(pipe_index >= px_num(chip)))
		return -EINVAL;
	if (snd_BUG_ON(!is_pipe_allocated(chip, pipe_index)))
		return -EINVAL;
	set_audio_format(chip, pipe_index, &format);
	return 0;
}