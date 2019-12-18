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
struct xfs_dir2_data_hdr {scalar_t__ magic; } ;
struct xfs_da_args {TYPE_2__* dp; int /*<<< orphan*/  trans; } ;
struct xfs_buf {struct xfs_dir2_data_hdr* b_addr; } ;
struct TYPE_4__ {TYPE_1__* d_ops; } ;
struct TYPE_3__ {scalar_t__ data_entry_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_DIR2_BLOCK_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_BLOCK_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_DATA_MAGIC ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (int /*<<< orphan*/ ,struct xfs_buf*,int /*<<< orphan*/ ,scalar_t__) ; 

void
xfs_dir2_data_log_header(
	struct xfs_da_args	*args,
	struct xfs_buf		*bp)
{
#ifdef DEBUG
	struct xfs_dir2_data_hdr *hdr = bp->b_addr;

	ASSERT(hdr->magic == cpu_to_be32(XFS_DIR2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR3_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR2_BLOCK_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR3_BLOCK_MAGIC));
#endif

	xfs_trans_log_buf(args->trans, bp, 0,
			  args->dp->d_ops->data_entry_offset - 1);
}