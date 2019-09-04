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
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __unbuffered_tpr_x ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  ss ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x ; 
 int /*<<< orphan*/  y ; 

void *thread_update(void *arg)
{
	WRITE_ONCE(y, 1);
#ifndef FORCE_FAILURE_2
	synchronize_srcu(&ss);
#endif
	might_sleep();
	__unbuffered_tpr_x = READ_ONCE(x);

	return NULL;
}