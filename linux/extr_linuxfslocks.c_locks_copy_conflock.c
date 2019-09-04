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
struct file_lock {int /*<<< orphan*/  fl_owner; TYPE_1__* fl_lmops; int /*<<< orphan*/ * fl_ops; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_flags; int /*<<< orphan*/ * fl_file; int /*<<< orphan*/  fl_pid; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* lm_get_owner ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void locks_copy_conflock(struct file_lock *new, struct file_lock *fl)
{
	new->fl_owner = fl->fl_owner;
	new->fl_pid = fl->fl_pid;
	new->fl_file = NULL;
	new->fl_flags = fl->fl_flags;
	new->fl_type = fl->fl_type;
	new->fl_start = fl->fl_start;
	new->fl_end = fl->fl_end;
	new->fl_lmops = fl->fl_lmops;
	new->fl_ops = NULL;

	if (fl->fl_lmops) {
		if (fl->fl_lmops->lm_get_owner)
			fl->fl_lmops->lm_get_owner(fl->fl_owner);
	}
}