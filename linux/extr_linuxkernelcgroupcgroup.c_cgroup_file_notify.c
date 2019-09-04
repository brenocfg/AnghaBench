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
struct cgroup_file {unsigned long notified_at; scalar_t__ kn; int /*<<< orphan*/  notify_timer; } ;

/* Variables and functions */
 unsigned long CGROUP_FILE_NOTIFY_MIN_INTV ; 
 int /*<<< orphan*/  cgroup_file_kn_lock ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kernfs_notify (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_in_range (unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  timer_reduce (int /*<<< orphan*/ *,unsigned long) ; 

void cgroup_file_notify(struct cgroup_file *cfile)
{
	unsigned long flags;

	spin_lock_irqsave(&cgroup_file_kn_lock, flags);
	if (cfile->kn) {
		unsigned long last = cfile->notified_at;
		unsigned long next = last + CGROUP_FILE_NOTIFY_MIN_INTV;

		if (time_in_range(jiffies, last, next)) {
			timer_reduce(&cfile->notify_timer, next);
		} else {
			kernfs_notify(cfile->kn);
			cfile->notified_at = jiffies;
		}
	}
	spin_unlock_irqrestore(&cgroup_file_kn_lock, flags);
}