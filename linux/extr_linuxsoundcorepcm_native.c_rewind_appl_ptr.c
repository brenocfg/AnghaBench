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
struct snd_pcm_runtime {scalar_t__ boundary; TYPE_1__* control; } ;
typedef  scalar_t__ snd_pcm_uframes_t ;
typedef  scalar_t__ snd_pcm_sframes_t ;
struct TYPE_2__ {scalar_t__ appl_ptr; } ;

/* Variables and functions */
 int pcm_lib_apply_appl_ptr (struct snd_pcm_substream*,scalar_t__) ; 

__attribute__((used)) static snd_pcm_sframes_t rewind_appl_ptr(struct snd_pcm_substream *substream,
					 snd_pcm_uframes_t frames,
					 snd_pcm_sframes_t avail)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	snd_pcm_sframes_t appl_ptr;
	int ret;

	if (avail <= 0)
		return 0;
	if (frames > (snd_pcm_uframes_t)avail)
		frames = avail;
	appl_ptr = runtime->control->appl_ptr - frames;
	if (appl_ptr < 0)
		appl_ptr += runtime->boundary;
	ret = pcm_lib_apply_appl_ptr(substream, appl_ptr);
	/* NOTE: we return zero for errors because PulseAudio gets depressed
	 * upon receiving an error from rewind ioctl and stops processing
	 * any longer.  Returning zero means that no rewind is done, so
	 * it's not absolutely wrong to answer like that.
	 */
	return ret < 0 ? 0 : frames;
}