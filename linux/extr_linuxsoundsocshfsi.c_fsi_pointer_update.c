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
struct snd_pcm_runtime {scalar_t__ periods; } ;
struct fsi_stream {int buff_sample_pos; int period_samples; int period_pos; struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 

__attribute__((used)) static void fsi_pointer_update(struct fsi_stream *io, int size)
{
	io->buff_sample_pos += size;

	if (io->buff_sample_pos >=
	    io->period_samples * (io->period_pos + 1)) {
		struct snd_pcm_substream *substream = io->substream;
		struct snd_pcm_runtime *runtime = substream->runtime;

		io->period_pos++;

		if (io->period_pos >= runtime->periods) {
			io->buff_sample_pos = 0;
			io->period_pos = 0;
		}

		snd_pcm_period_elapsed(substream);
	}
}