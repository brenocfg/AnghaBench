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
struct fprop_local_single {int /*<<< orphan*/  lock; scalar_t__ period; scalar_t__ events; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

int fprop_local_init_single(struct fprop_local_single *pl)
{
	pl->events = 0;
	pl->period = 0;
	raw_spin_lock_init(&pl->lock);
	return 0;
}