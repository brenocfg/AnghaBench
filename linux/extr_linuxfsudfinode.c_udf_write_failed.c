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
struct udf_inode_info {scalar_t__ i_alloc_type; int /*<<< orphan*/  i_data_sem; } ;
struct inode {scalar_t__ i_size; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  udf_clear_extent_cache (struct inode*) ; 
 int /*<<< orphan*/  udf_truncate_extents (struct inode*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void udf_write_failed(struct address_space *mapping, loff_t to)
{
	struct inode *inode = mapping->host;
	struct udf_inode_info *iinfo = UDF_I(inode);
	loff_t isize = inode->i_size;

	if (to > isize) {
		truncate_pagecache(inode, isize);
		if (iinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) {
			down_write(&iinfo->i_data_sem);
			udf_clear_extent_cache(inode);
			udf_truncate_extents(inode);
			up_write(&iinfo->i_data_sem);
		}
	}
}