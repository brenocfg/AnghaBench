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
struct snd_intelhad {int need_reset; } ;

/* Variables and functions */
 struct snd_pcm_substream* had_substream_get (struct snd_intelhad*) ; 
 int /*<<< orphan*/  had_substream_put (struct snd_intelhad*) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (struct snd_pcm_substream*) ; 

__attribute__((used)) static void had_process_buffer_underrun(struct snd_intelhad *intelhaddata)
{
	struct snd_pcm_substream *substream;

	/* Report UNDERRUN error to above layers */
	substream = had_substream_get(intelhaddata);
	if (substream) {
		snd_pcm_stop_xrun(substream);
		had_substream_put(intelhaddata);
	}
	intelhaddata->need_reset = true;
}