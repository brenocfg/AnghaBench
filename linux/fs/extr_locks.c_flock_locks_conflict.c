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
struct file_lock {scalar_t__ fl_file; int fl_type; } ;

/* Variables and functions */
 int LOCK_MAND ; 
 int locks_conflict (struct file_lock*,struct file_lock*) ; 

__attribute__((used)) static bool flock_locks_conflict(struct file_lock *caller_fl,
				 struct file_lock *sys_fl)
{
	/* FLOCK locks referring to the same filp do not conflict with
	 * each other.
	 */
	if (caller_fl->fl_file == sys_fl->fl_file)
		return false;
	if ((caller_fl->fl_type & LOCK_MAND) || (sys_fl->fl_type & LOCK_MAND))
		return false;

	return locks_conflict(caller_fl, sys_fl);
}