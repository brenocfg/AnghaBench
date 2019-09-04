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
struct dentry {int /*<<< orphan*/  d_fsdata; } ;
struct debugfs_fsdata {int /*<<< orphan*/  active_users; int /*<<< orphan*/  active_users_drained; void* real_fops; } ;

/* Variables and functions */
 unsigned long DEBUGFS_FSDATA_IS_REAL_FOPS_BIT ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 void* cmpxchg (int /*<<< orphan*/ *,void*,struct debugfs_fsdata*) ; 
 scalar_t__ d_unlinked (struct dentry*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct debugfs_fsdata*) ; 
 struct debugfs_fsdata* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

int debugfs_file_get(struct dentry *dentry)
{
	struct debugfs_fsdata *fsd;
	void *d_fsd;

	d_fsd = READ_ONCE(dentry->d_fsdata);
	if (!((unsigned long)d_fsd & DEBUGFS_FSDATA_IS_REAL_FOPS_BIT)) {
		fsd = d_fsd;
	} else {
		fsd = kmalloc(sizeof(*fsd), GFP_KERNEL);
		if (!fsd)
			return -ENOMEM;

		fsd->real_fops = (void *)((unsigned long)d_fsd &
					~DEBUGFS_FSDATA_IS_REAL_FOPS_BIT);
		refcount_set(&fsd->active_users, 1);
		init_completion(&fsd->active_users_drained);
		if (cmpxchg(&dentry->d_fsdata, d_fsd, fsd) != d_fsd) {
			kfree(fsd);
			fsd = READ_ONCE(dentry->d_fsdata);
		}
	}

	/*
	 * In case of a successful cmpxchg() above, this check is
	 * strictly necessary and must follow it, see the comment in
	 * __debugfs_remove_file().
	 * OTOH, if the cmpxchg() hasn't been executed or wasn't
	 * successful, this serves the purpose of not starving
	 * removers.
	 */
	if (d_unlinked(dentry))
		return -EIO;

	if (!refcount_inc_not_zero(&fsd->active_users))
		return -EIO;

	return 0;
}