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
struct notifier_block {int dummy; } ;
struct file_lock {int fl_flags; int /*<<< orphan*/  fl_file; } ;

/* Variables and functions */
 int FL_LEASE ; 
 int /*<<< orphan*/  file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_file_close_inode_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfsd_file_lease_notifier_call(struct notifier_block *nb, unsigned long arg,
			    void *data)
{
	struct file_lock *fl = data;

	/* Only close files for F_SETLEASE leases */
	if (fl->fl_flags & FL_LEASE)
		nfsd_file_close_inode_sync(file_inode(fl->fl_file));
	return 0;
}