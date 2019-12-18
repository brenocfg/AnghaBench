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
struct ceph_nfs_fh {int /*<<< orphan*/  ino; } ;

/* Variables and functions */
 int FILEID_BTRFS_WITH_PARENT ; 
 int FILEID_INO32_GEN ; 
 int FILEID_INO32_GEN_PARENT ; 
 struct dentry* __fh_to_dentry (struct super_block*,int /*<<< orphan*/ ) ; 
 struct dentry* __snapfh_to_dentry (struct super_block*,struct ceph_nfs_snapfh*,int) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *ceph_fh_to_dentry(struct super_block *sb,
					struct fid *fid,
					int fh_len, int fh_type)
{
	struct ceph_nfs_fh *fh = (void *)fid->raw;

	if (fh_type == FILEID_BTRFS_WITH_PARENT) {
		struct ceph_nfs_snapfh *sfh = (void *)fid->raw;
		return __snapfh_to_dentry(sb, sfh, false);
	}

	if (fh_type != FILEID_INO32_GEN  &&
	    fh_type != FILEID_INO32_GEN_PARENT)
		return NULL;
	if (fh_len < sizeof(*fh) / 4)
		return NULL;

	dout("fh_to_dentry %llx\n", fh->ino);
	return __fh_to_dentry(sb, fh->ino);
}