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
struct snd_soc_pcm_stream {char* stream_name; int channels_min; int channels_max; int formats; int /*<<< orphan*/  rates; } ;

/* Variables and functions */
 int SNDRV_PCM_FMTBIT_S16_LE ; 
 int SNDRV_PCM_FMTBIT_S32_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_8000_192000 ; 

__attribute__((used)) static void stm32_i2s_dai_init(struct snd_soc_pcm_stream *stream,
			       char *stream_name)
{
	stream->stream_name = stream_name;
	stream->channels_min = 1;
	stream->channels_max = 2;
	stream->rates = SNDRV_PCM_RATE_8000_192000;
	stream->formats = SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S32_LE;
}