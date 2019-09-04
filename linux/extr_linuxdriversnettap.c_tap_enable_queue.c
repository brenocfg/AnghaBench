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
struct tap_queue {int enabled; size_t queue_index; } ;
struct tap_dev {size_t numvtaps; int /*<<< orphan*/ * taps; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EINVAL ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tap_queue*) ; 

__attribute__((used)) static int tap_enable_queue(struct tap_dev *tap, struct file *file,
			    struct tap_queue *q)
{
	int err = -EINVAL;

	ASSERT_RTNL();

	if (q->enabled)
		goto out;

	err = 0;
	rcu_assign_pointer(tap->taps[tap->numvtaps], q);
	q->queue_index = tap->numvtaps;
	q->enabled = true;

	tap->numvtaps++;
out:
	return err;
}