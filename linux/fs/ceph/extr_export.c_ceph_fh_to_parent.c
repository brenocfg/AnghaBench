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
struct super_block {int dummy; } ;
struct fid {scalar_t__ raw; } ;
struct dentry {int dummy; } ;
struct ceph_nfs_snapfh {int dummy; } ;
struct ceph_nfs_confh {int /*<<< orphan*/  parent_ino; int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FILEID_BTRFS_WITH_PARENT ; 
 int FILEID_INO32_GEN_PARENT ; 
 struct dentry* __fh_to_dentry (struct super_block*,int /*<<< orphan*/ ) ; 
 struct dentry* __get_parent (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dentry* __snapfh_to_dentry (struct super_block*,struct ceph_nfs_snapfh*,int) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct dentry *ceph_fh_to_parent(struct super_block *sb,
					struct fid *fid,
					int fh_len, int fh_type)
{
	struct ceph_nfs_confh *cfh = (void *)fid->raw;
	struct dentry *dentry;

	if (fh_type == FILEID_BTRFS_WITH_PARENT) {
		struct ceph_nfs_snapfh *sfh = (void *)fid->raw;
		return __snapfh_to_dentry(sb, sfh, true);
	}

	if (fh_type != FILEID_INO32_GEN_PARENT)
		return NULL;
	if (fh_len < sizeof(*cfh) / 4)
		return NULL;

	dout("fh_to_parent %llx\n", cfh->parent_ino);
	dentry = __get_parent(sb, NULL, cfh->ino);
	if (unlikely(dentry == ERR_PTR(-ENOENT)))
		dentry = __fh_to_dentry(sb, cfh->parent_ino);
	return dentry;
}