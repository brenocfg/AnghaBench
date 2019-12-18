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
struct flock {scalar_t__ l_start; scalar_t__ l_len; int /*<<< orphan*/  l_type; scalar_t__ l_whence; int /*<<< orphan*/  l_pid; } ;
struct file_lock {scalar_t__ fl_start; scalar_t__ fl_end; int /*<<< orphan*/  fl_type; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 scalar_t__ OFFSET_MAX ; 
 scalar_t__ OFFT_OFFSET_MAX ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  locks_translate_pid (struct file_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_active_pid_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int posix_lock_to_flock(struct flock *flock, struct file_lock *fl)
{
	flock->l_pid = locks_translate_pid(fl, task_active_pid_ns(current));
#if BITS_PER_LONG == 32
	/*
	 * Make sure we can represent the posix lock via
	 * legacy 32bit flock.
	 */
	if (fl->fl_start > OFFT_OFFSET_MAX)
		return -EOVERFLOW;
	if (fl->fl_end != OFFSET_MAX && fl->fl_end > OFFT_OFFSET_MAX)
		return -EOVERFLOW;
#endif
	flock->l_start = fl->fl_start;
	flock->l_len = fl->fl_end == OFFSET_MAX ? 0 :
		fl->fl_end - fl->fl_start + 1;
	flock->l_whence = 0;
	flock->l_type = fl->fl_type;
	return 0;
}