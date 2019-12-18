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
struct snd_motu {int dev_lock_count; int /*<<< orphan*/  lock; } ;
struct snd_hwdep {struct snd_motu* private_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hwdep_release(struct snd_hwdep *hwdep, struct file *file)
{
	struct snd_motu *motu = hwdep->private_data;

	spin_lock_irq(&motu->lock);
	if (motu->dev_lock_count == -1)
		motu->dev_lock_count = 0;
	spin_unlock_irq(&motu->lock);

	return 0;
}