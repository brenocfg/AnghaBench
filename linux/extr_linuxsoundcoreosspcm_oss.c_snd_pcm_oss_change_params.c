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
struct TYPE_2__ {int /*<<< orphan*/  params_lock; } ;
struct snd_pcm_runtime {TYPE_1__ oss; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_pcm_oss_change_params_locked (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_oss_change_params(struct snd_pcm_substream *substream,
				     bool trylock)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;

	if (trylock) {
		if (!(mutex_trylock(&runtime->oss.params_lock)))
			return -EAGAIN;
	} else if (mutex_lock_interruptible(&runtime->oss.params_lock))
		return -ERESTARTSYS;

	err = snd_pcm_oss_change_params_locked(substream);
	mutex_unlock(&runtime->oss.params_lock);
	return err;
}