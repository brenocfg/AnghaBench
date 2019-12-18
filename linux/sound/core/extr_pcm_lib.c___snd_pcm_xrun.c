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
struct timespec {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  pcm; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ tstamp_mode; TYPE_1__* status; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int /*<<< orphan*/  tstamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STATE_XRUN ; 
 scalar_t__ SNDRV_PCM_TSTAMP_ENABLE ; 
 int /*<<< orphan*/  XRUN_DEBUG_BASIC ; 
 int /*<<< orphan*/  dump_stack_on_xrun (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  pcm_warn (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  snd_pcm_debug_name (struct snd_pcm_substream*,char*,int) ; 
 int /*<<< orphan*/  snd_pcm_gettime (struct snd_pcm_runtime*,struct timespec*) ; 
 int /*<<< orphan*/  snd_pcm_stop (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xrun (struct snd_pcm_substream*) ; 
 scalar_t__ xrun_debug (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

void __snd_pcm_xrun(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;

	trace_xrun(substream);
	if (runtime->tstamp_mode == SNDRV_PCM_TSTAMP_ENABLE)
		snd_pcm_gettime(runtime, (struct timespec *)&runtime->status->tstamp);
	snd_pcm_stop(substream, SNDRV_PCM_STATE_XRUN);
	if (xrun_debug(substream, XRUN_DEBUG_BASIC)) {
		char name[16];
		snd_pcm_debug_name(substream, name, sizeof(name));
		pcm_warn(substream->pcm, "XRUN: %s\n", name);
		dump_stack_on_xrun(substream);
	}
}