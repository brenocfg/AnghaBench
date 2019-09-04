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
struct snd_bebob {scalar_t__ dev_lock_count; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  snd_bebob_stream_lock_changed (struct snd_bebob*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int snd_bebob_stream_lock_try(struct snd_bebob *bebob)
{
	int err;

	spin_lock_irq(&bebob->lock);

	/* user land lock this */
	if (bebob->dev_lock_count < 0) {
		err = -EBUSY;
		goto end;
	}

	/* this is the first time */
	if (bebob->dev_lock_count++ == 0)
		snd_bebob_stream_lock_changed(bebob);
	err = 0;
end:
	spin_unlock_irq(&bebob->lock);
	return err;
}