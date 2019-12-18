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
struct nilfs_fid {int /*<<< orphan*/  parent_gen; int /*<<< orphan*/  parent_ino; int /*<<< orphan*/  cno; } ;
struct fid {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int FILEID_NILFS_WITH_PARENT ; 
 int NILFS_FID_SIZE_CONNECTABLE ; 
 struct dentry* nilfs_get_dentry (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *nilfs_fh_to_parent(struct super_block *sb, struct fid *fh,
					 int fh_len, int fh_type)
{
	struct nilfs_fid *fid = (struct nilfs_fid *)fh;

	if (fh_len < NILFS_FID_SIZE_CONNECTABLE ||
	    fh_type != FILEID_NILFS_WITH_PARENT)
		return NULL;

	return nilfs_get_dentry(sb, fid->cno, fid->parent_ino, fid->parent_gen);
}