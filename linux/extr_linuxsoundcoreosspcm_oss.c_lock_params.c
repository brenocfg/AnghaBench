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
struct TYPE_2__ {int /*<<< orphan*/  params_lock; int /*<<< orphan*/  rw_ref; } ;
struct snd_pcm_runtime {TYPE_1__ oss; } ;

/* Variables and functions */
 int EBUSY ; 
 int ERESTARTSYS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lock_params(struct snd_pcm_runtime *runtime)
{
	if (mutex_lock_interruptible(&runtime->oss.params_lock))
		return -ERESTARTSYS;
	if (atomic_read(&runtime->oss.rw_ref)) {
		mutex_unlock(&runtime->oss.params_lock);
		return -EBUSY;
	}
	return 0;
}