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
struct snd_pcm_runtime {struct snd_pcm_substream* trigger_master; int /*<<< orphan*/  trigger_tstamp; int /*<<< orphan*/  trigger_tstamp_latched; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_gettime (struct snd_pcm_runtime*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_pcm_trigger_tstamp(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	if (runtime->trigger_master == NULL)
		return;
	if (runtime->trigger_master == substream) {
		if (!runtime->trigger_tstamp_latched)
			snd_pcm_gettime(runtime, &runtime->trigger_tstamp);
	} else {
		snd_pcm_trigger_tstamp(runtime->trigger_master);
		runtime->trigger_tstamp = runtime->trigger_master->runtime->trigger_tstamp;
	}
	runtime->trigger_master = NULL;
}