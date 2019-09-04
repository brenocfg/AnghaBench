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
struct fuse_file_lock {int type; int /*<<< orphan*/  pid; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct fuse_conn {int /*<<< orphan*/  pid_ns; } ;
struct file_lock {int fl_type; int /*<<< orphan*/  fl_pid; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; } ;

/* Variables and functions */
 int EIO ; 
#define  F_RDLCK 130 
#define  F_UNLCK 129 
#define  F_WRLCK 128 
 int /*<<< orphan*/  OFFSET_MAX ; 
 int /*<<< orphan*/  find_pid_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_pid_ns ; 
 int /*<<< orphan*/  pid_nr_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int convert_fuse_file_lock(struct fuse_conn *fc,
				  const struct fuse_file_lock *ffl,
				  struct file_lock *fl)
{
	switch (ffl->type) {
	case F_UNLCK:
		break;

	case F_RDLCK:
	case F_WRLCK:
		if (ffl->start > OFFSET_MAX || ffl->end > OFFSET_MAX ||
		    ffl->end < ffl->start)
			return -EIO;

		fl->fl_start = ffl->start;
		fl->fl_end = ffl->end;

		/*
		 * Convert pid into init's pid namespace.  The locks API will
		 * translate it into the caller's pid namespace.
		 */
		rcu_read_lock();
		fl->fl_pid = pid_nr_ns(find_pid_ns(ffl->pid, fc->pid_ns), &init_pid_ns);
		rcu_read_unlock();
		break;

	default:
		return -EIO;
	}
	fl->fl_type = ffl->type;
	return 0;
}