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
typedef  void* u32 ;
struct super_block {int dummy; } ;
struct kernel_lb_addr {void* partitionReferenceNum; void* logicalBlockNum; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_alloc_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ ICBTAG_FLAG_AD_SHORT ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 TYPE_1__* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* udf_iget_special (struct super_block*,struct kernel_lb_addr*) ; 
 int /*<<< orphan*/  udf_warn (struct super_block*,char*) ; 

struct inode *udf_find_metadata_inode_efe(struct super_block *sb,
					u32 meta_file_loc, u32 partition_ref)
{
	struct kernel_lb_addr addr;
	struct inode *metadata_fe;

	addr.logicalBlockNum = meta_file_loc;
	addr.partitionReferenceNum = partition_ref;

	metadata_fe = udf_iget_special(sb, &addr);

	if (IS_ERR(metadata_fe)) {
		udf_warn(sb, "metadata inode efe not found\n");
		return metadata_fe;
	}
	if (UDF_I(metadata_fe)->i_alloc_type != ICBTAG_FLAG_AD_SHORT) {
		udf_warn(sb, "metadata inode efe does not have short allocation descriptors!\n");
		iput(metadata_fe);
		return ERR_PTR(-EIO);
	}

	return metadata_fe;
}