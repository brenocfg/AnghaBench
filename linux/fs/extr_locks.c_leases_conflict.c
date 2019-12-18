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
struct file_lock {int fl_flags; } ;

/* Variables and functions */
 int FL_DELEG ; 
 int FL_LAYOUT ; 
 int FL_LEASE ; 
 int locks_conflict (struct file_lock*,struct file_lock*) ; 
 int /*<<< orphan*/  trace_leases_conflict (int,struct file_lock*,struct file_lock*) ; 

__attribute__((used)) static bool leases_conflict(struct file_lock *lease, struct file_lock *breaker)
{
	bool rc;

	if ((breaker->fl_flags & FL_LAYOUT) != (lease->fl_flags & FL_LAYOUT)) {
		rc = false;
		goto trace;
	}
	if ((breaker->fl_flags & FL_DELEG) && (lease->fl_flags & FL_LEASE)) {
		rc = false;
		goto trace;
	}

	rc = locks_conflict(breaker, lease);
trace:
	trace_leases_conflict(rc, lease, breaker);
	return rc;
}