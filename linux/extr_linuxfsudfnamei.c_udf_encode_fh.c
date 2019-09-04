#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kernel_lb_addr {scalar_t__ partitionReferenceNum; int /*<<< orphan*/  logicalBlockNum; } ;
struct inode {int /*<<< orphan*/  i_generation; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent_generation; scalar_t__ parent_partref; int /*<<< orphan*/  parent_block; int /*<<< orphan*/  generation; scalar_t__ partref; int /*<<< orphan*/  block; } ;
struct fid {TYPE_1__ udf; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {struct kernel_lb_addr i_location; } ;

/* Variables and functions */
 int FILEID_INVALID ; 
 int FILEID_UDF_WITHOUT_PARENT ; 
 int FILEID_UDF_WITH_PARENT ; 
 TYPE_2__* UDF_I (struct inode*) ; 

__attribute__((used)) static int udf_encode_fh(struct inode *inode, __u32 *fh, int *lenp,
			 struct inode *parent)
{
	int len = *lenp;
	struct kernel_lb_addr location = UDF_I(inode)->i_location;
	struct fid *fid = (struct fid *)fh;
	int type = FILEID_UDF_WITHOUT_PARENT;

	if (parent && (len < 5)) {
		*lenp = 5;
		return FILEID_INVALID;
	} else if (len < 3) {
		*lenp = 3;
		return FILEID_INVALID;
	}

	*lenp = 3;
	fid->udf.block = location.logicalBlockNum;
	fid->udf.partref = location.partitionReferenceNum;
	fid->udf.parent_partref = 0;
	fid->udf.generation = inode->i_generation;

	if (parent) {
		location = UDF_I(parent)->i_location;
		fid->udf.parent_block = location.logicalBlockNum;
		fid->udf.parent_partref = location.partitionReferenceNum;
		fid->udf.parent_generation = inode->i_generation;
		*lenp = 5;
		type = FILEID_UDF_WITH_PARENT;
	}

	return type;
}