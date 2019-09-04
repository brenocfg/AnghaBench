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
struct snd_pcm_substream {int dummy; } ;
struct snd_intelhad {int /*<<< orphan*/  connected; } ;

/* Variables and functions */
 scalar_t__ had_process_ringbuf (struct snd_pcm_substream*,struct snd_intelhad*) ; 
 struct snd_pcm_substream* had_substream_get (struct snd_intelhad*) ; 
 int /*<<< orphan*/  had_substream_put (struct snd_intelhad*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (struct snd_pcm_substream*) ; 

__attribute__((used)) static void had_process_buffer_done(struct snd_intelhad *intelhaddata)
{
	struct snd_pcm_substream *substream;

	substream = had_substream_get(intelhaddata);
	if (!substream)
		return; /* no stream? - bail out */

	if (!intelhaddata->connected) {
		snd_pcm_stop_xrun(substream);
		goto out; /* disconnected? - bail out */
	}

	/* process or stop the stream */
	if (had_process_ringbuf(substream, intelhaddata) < 0)
		snd_pcm_stop_xrun(substream);
	else
		snd_pcm_period_elapsed(substream);

 out:
	had_substream_put(intelhaddata);
}