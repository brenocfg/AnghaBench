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
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCOV_ADD ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  gcov_event (int /*<<< orphan*/ ,struct gcov_info*) ; 
 int gcov_events_enabled ; 
 struct gcov_info* gcov_info_next (struct gcov_info*) ; 
 int /*<<< orphan*/  gcov_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void gcov_enable_events(void)
{
	struct gcov_info *info = NULL;

	mutex_lock(&gcov_lock);
	gcov_events_enabled = 1;

	/* Perform event callback for previously registered entries. */
	while ((info = gcov_info_next(info))) {
		gcov_event(GCOV_ADD, info);
		cond_resched();
	}

	mutex_unlock(&gcov_lock);
}