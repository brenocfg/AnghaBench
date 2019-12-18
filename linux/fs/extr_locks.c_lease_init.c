#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file_lock {int /*<<< orphan*/ * fl_lmops; int /*<<< orphan*/ * fl_ops; int /*<<< orphan*/  fl_end; scalar_t__ fl_start; int /*<<< orphan*/  fl_flags; struct file* fl_file; int /*<<< orphan*/  fl_pid; struct file* fl_owner; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FL_LEASE ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 scalar_t__ assign_type (struct file_lock*,long) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  lease_manager_ops ; 

__attribute__((used)) static int lease_init(struct file *filp, long type, struct file_lock *fl)
{
	if (assign_type(fl, type) != 0)
		return -EINVAL;

	fl->fl_owner = filp;
	fl->fl_pid = current->tgid;

	fl->fl_file = filp;
	fl->fl_flags = FL_LEASE;
	fl->fl_start = 0;
	fl->fl_end = OFFSET_MAX;
	fl->fl_ops = NULL;
	fl->fl_lmops = &lease_manager_ops;
	return 0;
}