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
struct TYPE_2__ {int /*<<< orphan*/  params_lock; scalar_t__ prepare; scalar_t__ params; } ;
struct snd_pcm_runtime {TYPE_1__ oss; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_pcm_oss_change_params (struct snd_pcm_substream*,int) ; 
 int snd_pcm_oss_prepare (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_oss_make_ready(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime;
	int err;

	runtime = substream->runtime;
	if (runtime->oss.params) {
		err = snd_pcm_oss_change_params(substream, false);
		if (err < 0)
			return err;
	}
	if (runtime->oss.prepare) {
		if (mutex_lock_interruptible(&runtime->oss.params_lock))
			return -ERESTARTSYS;
		err = snd_pcm_oss_prepare(substream);
		mutex_unlock(&runtime->oss.params_lock);
		if (err < 0)
			return err;
	}
	return 0;
}