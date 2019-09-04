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
struct unallocSpaceEntry {int dummy; } ;
struct udf_inode_info {size_t i_lenEAttr; scalar_t__ i_efe; scalar_t__ i_use; } ;
struct inode {int dummy; } ;
struct fileEntry {int dummy; } ;
struct extendedFileEntry {int dummy; } ;

/* Variables and functions */
 struct udf_inode_info* UDF_I (struct inode*) ; 

__attribute__((used)) static inline size_t udf_file_entry_alloc_offset(struct inode *inode)
{
	struct udf_inode_info *iinfo = UDF_I(inode);
	if (iinfo->i_use)
		return sizeof(struct unallocSpaceEntry);
	else if (iinfo->i_efe)
		return sizeof(struct extendedFileEntry) + iinfo->i_lenEAttr;
	else
		return sizeof(struct fileEntry) + iinfo->i_lenEAttr;
}