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
struct TYPE_2__ {int /*<<< orphan*/ * i_data; } ;
struct udf_inode_info {scalar_t__ i_alloc_type; scalar_t__ i_lenExtents; TYPE_1__ i_ext; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_nlink; } ;

/* Variables and functions */
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 int /*<<< orphan*/  IS_SYNC (struct inode*) ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  invalidate_inode_buffers (struct inode*) ; 
 int /*<<< orphan*/  is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udf_clear_extent_cache (struct inode*) ; 
 int /*<<< orphan*/  udf_free_inode (struct inode*) ; 
 int /*<<< orphan*/  udf_setsize (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_update_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 

void udf_evict_inode(struct inode *inode)
{
	struct udf_inode_info *iinfo = UDF_I(inode);
	int want_delete = 0;

	if (!inode->i_nlink && !is_bad_inode(inode)) {
		want_delete = 1;
		udf_setsize(inode, 0);
		udf_update_inode(inode, IS_SYNC(inode));
	}
	truncate_inode_pages_final(&inode->i_data);
	invalidate_inode_buffers(inode);
	clear_inode(inode);
	if (iinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB &&
	    inode->i_size != iinfo->i_lenExtents) {
		udf_warn(inode->i_sb, "Inode %lu (mode %o) has inode size %llu different from extent length %llu. Filesystem need not be standards compliant.\n",
			 inode->i_ino, inode->i_mode,
			 (unsigned long long)inode->i_size,
			 (unsigned long long)iinfo->i_lenExtents);
	}
	kfree(iinfo->i_ext.i_data);
	iinfo->i_ext.i_data = NULL;
	udf_clear_extent_cache(inode);
	if (want_delete) {
		udf_free_inode(inode);
	}
}