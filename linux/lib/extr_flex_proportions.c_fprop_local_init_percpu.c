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
struct fprop_local_percpu {int /*<<< orphan*/  lock; scalar_t__ period; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int percpu_counter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

int fprop_local_init_percpu(struct fprop_local_percpu *pl, gfp_t gfp)
{
	int err;

	err = percpu_counter_init(&pl->events, 0, gfp);
	if (err)
		return err;
	pl->period = 0;
	raw_spin_lock_init(&pl->lock);
	return 0;
}