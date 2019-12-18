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
typedef  scalar_t__ uint16_t ;
struct super_block {int dummy; } ;
struct kernel_lb_addr {int logicalBlockNum; int partitionReferenceNum; } ;
struct fileSetDesc {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {int s_partition; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ TAG_IDENT_FSD ; 
 TYPE_1__* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  udf_debug (char*,int,int) ; 
 int udf_load_fileset (struct super_block*,struct fileSetDesc*,struct kernel_lb_addr*) ; 
 struct buffer_head* udf_read_ptagged (struct super_block*,struct kernel_lb_addr*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int udf_find_fileset(struct super_block *sb,
			    struct kernel_lb_addr *fileset,
			    struct kernel_lb_addr *root)
{
	struct buffer_head *bh = NULL;
	uint16_t ident;
	int ret;

	if (fileset->logicalBlockNum == 0xFFFFFFFF &&
	    fileset->partitionReferenceNum == 0xFFFF)
		return -EINVAL;

	bh = udf_read_ptagged(sb, fileset, 0, &ident);
	if (!bh)
		return -EIO;
	if (ident != TAG_IDENT_FSD) {
		brelse(bh);
		return -EINVAL;
	}

	udf_debug("Fileset at block=%u, partition=%u\n",
		  fileset->logicalBlockNum, fileset->partitionReferenceNum);

	UDF_SB(sb)->s_partition = fileset->partitionReferenceNum;
	ret = udf_load_fileset(sb, (struct fileSetDesc *)bh->b_data, root);
	brelse(bh);
	return ret;
}