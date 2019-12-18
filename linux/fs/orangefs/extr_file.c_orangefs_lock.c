#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file_lock {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int EINVAL ; 
 int F_GETLK ; 
 int ORANGEFS_OPT_LOCAL_LOCK ; 
 TYPE_2__* ORANGEFS_SB (int /*<<< orphan*/ ) ; 
 TYPE_1__* file_inode (struct file*) ; 
 int posix_lock_file (struct file*,struct file_lock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  posix_test_lock (struct file*,struct file_lock*) ; 

__attribute__((used)) static int orangefs_lock(struct file *filp, int cmd, struct file_lock *fl)
{
	int rc = -EINVAL;

	if (ORANGEFS_SB(file_inode(filp)->i_sb)->flags & ORANGEFS_OPT_LOCAL_LOCK) {
		if (cmd == F_GETLK) {
			rc = 0;
			posix_test_lock(filp, fl);
		} else {
			rc = posix_lock_file(filp, fl, NULL);
		}
	}

	return rc;
}