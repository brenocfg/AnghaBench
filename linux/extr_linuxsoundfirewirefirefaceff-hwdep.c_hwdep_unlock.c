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
struct snd_ff {int dev_lock_count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBADFD ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hwdep_unlock(struct snd_ff *ff)
{
	int err;

	spin_lock_irq(&ff->lock);

	if (ff->dev_lock_count == -1) {
		ff->dev_lock_count = 0;
		err = 0;
	} else {
		err = -EBADFD;
	}

	spin_unlock_irq(&ff->lock);

	return err;
}