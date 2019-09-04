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
struct snd_pcm_substream {int stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct loopback_pcm* private_data; } ;
struct loopback_pcm {TYPE_1__* loopback; struct loopback_cable* cable; } ;
struct loopback_cable {int valid; } ;
struct TYPE_2__ {int /*<<< orphan*/  cable_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_pcm_lib_free_vmalloc_buffer (struct snd_pcm_substream*) ; 

__attribute__((used)) static int loopback_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct loopback_pcm *dpcm = runtime->private_data;
	struct loopback_cable *cable = dpcm->cable;

	mutex_lock(&dpcm->loopback->cable_lock);
	cable->valid &= ~(1 << substream->stream);
	mutex_unlock(&dpcm->loopback->cable_lock);
	return snd_pcm_lib_free_vmalloc_buffer(substream);
}