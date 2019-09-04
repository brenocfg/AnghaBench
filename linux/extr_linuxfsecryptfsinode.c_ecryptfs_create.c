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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate_new (struct dentry*,struct inode*) ; 
 struct inode* ecryptfs_do_create (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecryptfs_do_unlink (struct inode*,struct dentry*,struct inode*) ; 
 int ecryptfs_initialize_file (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 

__attribute__((used)) static int
ecryptfs_create(struct inode *directory_inode, struct dentry *ecryptfs_dentry,
		umode_t mode, bool excl)
{
	struct inode *ecryptfs_inode;
	int rc;

	ecryptfs_inode = ecryptfs_do_create(directory_inode, ecryptfs_dentry,
					    mode);
	if (IS_ERR(ecryptfs_inode)) {
		ecryptfs_printk(KERN_WARNING, "Failed to create file in"
				"lower filesystem\n");
		rc = PTR_ERR(ecryptfs_inode);
		goto out;
	}
	/* At this point, a file exists on "disk"; we need to make sure
	 * that this on disk file is prepared to be an ecryptfs file */
	rc = ecryptfs_initialize_file(ecryptfs_dentry, ecryptfs_inode);
	if (rc) {
		ecryptfs_do_unlink(directory_inode, ecryptfs_dentry,
				   ecryptfs_inode);
		iget_failed(ecryptfs_inode);
		goto out;
	}
	d_instantiate_new(ecryptfs_dentry, ecryptfs_inode);
out:
	return rc;
}