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

/* Variables and functions */
 int __refrigerator (int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  freezing (int /*<<< orphan*/ ) ; 
 int kthread_should_stop () ; 
 int /*<<< orphan*/  might_sleep () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

bool kthread_freezable_should_stop(bool *was_frozen)
{
	bool frozen = false;

	might_sleep();

	if (unlikely(freezing(current)))
		frozen = __refrigerator(true);

	if (was_frozen)
		*was_frozen = frozen;

	return kthread_should_stop();
}