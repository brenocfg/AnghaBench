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
struct snd_pcm_runtime {int channels; } ;
typedef  int snd_pcm_uframes_t ;
typedef  int (* pcm_transfer_f ) (struct snd_pcm_substream*,int,int,void*,int) ;

/* Variables and functions */
 int fill_silence (struct snd_pcm_substream*,int,int,int /*<<< orphan*/ *,int) ; 
 int samples_to_bytes (struct snd_pcm_runtime*,int) ; 

__attribute__((used)) static int noninterleaved_copy(struct snd_pcm_substream *substream,
			       snd_pcm_uframes_t hwoff, void *data,
			       snd_pcm_uframes_t off,
			       snd_pcm_uframes_t frames,
			       pcm_transfer_f transfer)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int channels = runtime->channels;
	void **bufs = data;
	int c, err;

	/* convert to bytes; note that it's not frames_to_bytes() here.
	 * in non-interleaved mode, we copy for each channel, thus
	 * each copy is n_samples bytes x channels = whole frames.
	 */
	off = samples_to_bytes(runtime, off);
	frames = samples_to_bytes(runtime, frames);
	hwoff = samples_to_bytes(runtime, hwoff);
	for (c = 0; c < channels; ++c, ++bufs) {
		if (!data || !*bufs)
			err = fill_silence(substream, c, hwoff, NULL, frames);
		else
			err = transfer(substream, c, hwoff, *bufs + off,
				       frames);
		if (err < 0)
			return err;
	}
	return 0;
}