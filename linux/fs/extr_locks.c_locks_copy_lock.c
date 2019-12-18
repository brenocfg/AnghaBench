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
struct file_lock {TYPE_1__* fl_ops; int /*<<< orphan*/  fl_file; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fl_copy_lock ) (struct file_lock*,struct file_lock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (TYPE_1__*) ; 
 int /*<<< orphan*/  locks_copy_conflock (struct file_lock*,struct file_lock*) ; 
 int /*<<< orphan*/  stub1 (struct file_lock*,struct file_lock*) ; 

void locks_copy_lock(struct file_lock *new, struct file_lock *fl)
{
	/* "new" must be a freshly-initialized lock */
	WARN_ON_ONCE(new->fl_ops);

	locks_copy_conflock(new, fl);

	new->fl_file = fl->fl_file;
	new->fl_ops = fl->fl_ops;

	if (fl->fl_ops) {
		if (fl->fl_ops->fl_copy_lock)
			fl->fl_ops->fl_copy_lock(new, fl);
	}
}