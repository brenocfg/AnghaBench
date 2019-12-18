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
struct file_lock {int fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_flags; int /*<<< orphan*/  fl_pid; struct file* fl_owner; struct file* fl_file; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct file_lock* ERR_PTR (int) ; 
 int /*<<< orphan*/  FL_FLOCK ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 TYPE_1__* current ; 
 int flock_translate_cmd (unsigned int) ; 
 struct file_lock* locks_alloc_lock () ; 
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 

__attribute__((used)) static struct file_lock *
flock_make_lock(struct file *filp, unsigned int cmd, struct file_lock *fl)
{
	int type = flock_translate_cmd(cmd);

	if (type < 0)
		return ERR_PTR(type);

	if (fl == NULL) {
		fl = locks_alloc_lock();
		if (fl == NULL)
			return ERR_PTR(-ENOMEM);
	} else {
		locks_init_lock(fl);
	}

	fl->fl_file = filp;
	fl->fl_owner = filp;
	fl->fl_pid = current->tgid;
	fl->fl_flags = FL_FLOCK;
	fl->fl_type = type;
	fl->fl_end = OFFSET_MAX;

	return fl;
}