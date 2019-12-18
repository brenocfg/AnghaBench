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
struct integrity_iint_cache {scalar_t__ ima_file_status; int flags; int /*<<< orphan*/  atomic_flags; } ;
struct file {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMA_DIGSIG ; 
 int IMA_HASH ; 
 scalar_t__ INTEGRITY_PASS ; 
 struct dentry* file_dentry (struct file*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int ima_collect_measurement (struct integrity_iint_cache*,struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ima_fix_xattr (struct dentry*,struct integrity_iint_cache*) ; 
 int /*<<< orphan*/  ima_hash_algo ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ima_update_xattr(struct integrity_iint_cache *iint, struct file *file)
{
	struct dentry *dentry = file_dentry(file);
	int rc = 0;

	/* do not collect and update hash for digital signatures */
	if (test_bit(IMA_DIGSIG, &iint->atomic_flags))
		return;

	if ((iint->ima_file_status != INTEGRITY_PASS) &&
	    !(iint->flags & IMA_HASH))
		return;

	rc = ima_collect_measurement(iint, file, NULL, 0, ima_hash_algo, NULL);
	if (rc < 0)
		return;

	inode_lock(file_inode(file));
	ima_fix_xattr(dentry, iint);
	inode_unlock(file_inode(file));
}