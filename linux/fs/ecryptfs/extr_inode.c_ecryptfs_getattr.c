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
typedef  int /*<<< orphan*/  u32 ;
struct path {struct dentry* dentry; } ;
struct kstat {int /*<<< orphan*/  blocks; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  ecryptfs_dentry_to_lower_path (struct dentry*) ; 
 int /*<<< orphan*/  ecryptfs_inode_to_lower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsstack_copy_attr_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (int /*<<< orphan*/ ,struct kstat*) ; 
 int vfs_getattr (int /*<<< orphan*/ ,struct kstat*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ecryptfs_getattr(const struct path *path, struct kstat *stat,
			    u32 request_mask, unsigned int flags)
{
	struct dentry *dentry = path->dentry;
	struct kstat lower_stat;
	int rc;

	rc = vfs_getattr(ecryptfs_dentry_to_lower_path(dentry), &lower_stat,
			 request_mask, flags);
	if (!rc) {
		fsstack_copy_attr_all(d_inode(dentry),
				      ecryptfs_inode_to_lower(d_inode(dentry)));
		generic_fillattr(d_inode(dentry), stat);
		stat->blocks = lower_stat.blocks;
	}
	return rc;
}