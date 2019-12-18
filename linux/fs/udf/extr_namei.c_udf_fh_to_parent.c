#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent_generation; int /*<<< orphan*/  parent_partref; int /*<<< orphan*/  parent_block; } ;
struct fid {TYPE_1__ udf; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int FILEID_UDF_WITH_PARENT ; 
 struct dentry* udf_nfs_get_inode (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *udf_fh_to_parent(struct super_block *sb,
				       struct fid *fid, int fh_len, int fh_type)
{
	if (fh_len < 5 || fh_type != FILEID_UDF_WITH_PARENT)
		return NULL;

	return udf_nfs_get_inode(sb, fid->udf.parent_block,
				 fid->udf.parent_partref,
				 fid->udf.parent_generation);
}