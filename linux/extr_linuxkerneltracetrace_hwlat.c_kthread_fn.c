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
typedef  int u64 ;
struct TYPE_2__ {int sample_window; int sample_width; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  USEC_PER_MSEC ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_sample () ; 
 TYPE_1__ hwlat_data ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  move_to_next_cpu () ; 
 scalar_t__ msleep_interruptible (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kthread_fn(void *data)
{
	u64 interval;

	while (!kthread_should_stop()) {

		move_to_next_cpu();

		local_irq_disable();
		get_sample();
		local_irq_enable();

		mutex_lock(&hwlat_data.lock);
		interval = hwlat_data.sample_window - hwlat_data.sample_width;
		mutex_unlock(&hwlat_data.lock);

		do_div(interval, USEC_PER_MSEC); /* modifies interval value */

		/* Always sleep for at least 1ms */
		if (interval < 1)
			interval = 1;

		if (msleep_interruptible(interval))
			break;
	}

	return 0;
}