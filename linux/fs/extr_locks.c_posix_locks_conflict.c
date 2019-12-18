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
struct file_lock {int dummy; } ;

/* Variables and functions */
 int locks_conflict (struct file_lock*,struct file_lock*) ; 
 int /*<<< orphan*/  locks_overlap (struct file_lock*,struct file_lock*) ; 
 scalar_t__ posix_same_owner (struct file_lock*,struct file_lock*) ; 

__attribute__((used)) static bool posix_locks_conflict(struct file_lock *caller_fl,
				 struct file_lock *sys_fl)
{
	/* POSIX locks owned by the same process do not conflict with
	 * each other.
	 */
	if (posix_same_owner(caller_fl, sys_fl))
		return false;

	/* Check whether they overlap */
	if (!locks_overlap(caller_fl, sys_fl))
		return false;

	return locks_conflict(caller_fl, sys_fl);
}