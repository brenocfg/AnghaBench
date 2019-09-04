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
struct snd_hwdep {struct snd_bebob* private_data; } ;
struct snd_bebob {int dev_lock_count; int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hwdep_release(struct snd_hwdep *hwdep, struct file *file)
{
	struct snd_bebob *bebob = hwdep->private_data;

	spin_lock_irq(&bebob->lock);
	if (bebob->dev_lock_count == -1)
		bebob->dev_lock_count = 0;
	spin_unlock_irq(&bebob->lock);

	return 0;
}