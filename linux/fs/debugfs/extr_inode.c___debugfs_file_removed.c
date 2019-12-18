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
struct debugfs_fsdata {int /*<<< orphan*/  active_users_drained; int /*<<< orphan*/  active_users; } ;

/* Variables and functions */
 unsigned long DEBUGFS_FSDATA_IS_REAL_FOPS_BIT ; 
 struct debugfs_fsdata* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __debugfs_file_removed(struct dentry *dentry)
{
	struct debugfs_fsdata *fsd;

	/*
	 * Paired with the closing smp_mb() implied by a successful
	 * cmpxchg() in debugfs_file_get(): either
	 * debugfs_file_get() must see a dead dentry or we must see a
	 * debugfs_fsdata instance at ->d_fsdata here (or both).
	 */
	smp_mb();
	fsd = READ_ONCE(dentry->d_fsdata);
	if ((unsigned long)fsd & DEBUGFS_FSDATA_IS_REAL_FOPS_BIT)
		return;
	if (!refcount_dec_and_test(&fsd->active_users))
		wait_for_completion(&fsd->active_users_drained);
}