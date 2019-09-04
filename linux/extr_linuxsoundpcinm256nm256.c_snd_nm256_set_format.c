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
struct snd_pcm_substream {int stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int /*<<< orphan*/  rate; int /*<<< orphan*/  format; } ;
struct nm256_stream {scalar_t__ shift; } ;
struct nm256 {int dummy; } ;

/* Variables and functions */
 scalar_t__ NM_PLAYBACK_REG_OFFSET ; 
 unsigned char NM_RATE_BITS_16 ; 
 int NM_RATE_MASK ; 
 scalar_t__ NM_RATE_REG_OFFSET ; 
 unsigned char NM_RATE_STEREO ; 
 scalar_t__ NM_RECORD_REG_OFFSET ; 
#define  SNDRV_PCM_STREAM_CAPTURE 129 
#define  SNDRV_PCM_STREAM_PLAYBACK 128 
 int /*<<< orphan*/ * samplerates ; 
 int snd_nm256_fixed_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_nm256_load_coefficient (struct nm256*,int,int) ; 
 int /*<<< orphan*/  snd_nm256_writeb (struct nm256*,scalar_t__,unsigned char) ; 
 int snd_pcm_format_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snd_nm256_set_format(struct nm256 *chip, struct nm256_stream *s,
		     struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int rate_index = snd_nm256_fixed_rate(runtime->rate);
	unsigned char ratebits = (rate_index << 4) & NM_RATE_MASK;

	s->shift = 0;
	if (snd_pcm_format_width(runtime->format) == 16) {
		ratebits |= NM_RATE_BITS_16;
		s->shift++;
	}
	if (runtime->channels > 1) {
		ratebits |= NM_RATE_STEREO;
		s->shift++;
	}

	runtime->rate = samplerates[rate_index];

	switch (substream->stream) {
	case SNDRV_PCM_STREAM_PLAYBACK:
		snd_nm256_load_coefficient(chip, 0, rate_index); /* 0 = playback */
		snd_nm256_writeb(chip,
				 NM_PLAYBACK_REG_OFFSET + NM_RATE_REG_OFFSET,
				 ratebits);
		break;
	case SNDRV_PCM_STREAM_CAPTURE:
		snd_nm256_load_coefficient(chip, 1, rate_index); /* 1 = record */
		snd_nm256_writeb(chip,
				 NM_RECORD_REG_OFFSET + NM_RATE_REG_OFFSET,
				 ratebits);
		break;
	}
}