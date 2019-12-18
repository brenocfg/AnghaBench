#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ oss; } ;
struct snd_pcm_substream {TYPE_2__ oss; struct snd_pcm_runtime* runtime; } ;
struct TYPE_3__ {int /*<<< orphan*/ * buffer; } ;
struct snd_pcm_runtime {TYPE_1__ oss; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_oss_plugin_clear (struct snd_pcm_substream*) ; 

__attribute__((used)) static void snd_pcm_oss_release_substream(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime;
	runtime = substream->runtime;
	kvfree(runtime->oss.buffer);
	runtime->oss.buffer = NULL;
#ifdef CONFIG_SND_PCM_OSS_PLUGINS
	snd_pcm_oss_plugin_clear(substream);
#endif
	substream->oss.oss = 0;
}