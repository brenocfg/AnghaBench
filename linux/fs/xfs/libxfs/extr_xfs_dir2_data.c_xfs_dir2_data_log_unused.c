#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ xfs_dir2_data_unused_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_off_t ;
struct TYPE_6__ {scalar_t__ magic; } ;
typedef  TYPE_2__ xfs_dir2_data_hdr_t ;
typedef  int /*<<< orphan*/  uint ;
struct xfs_da_args {int /*<<< orphan*/  trans; } ;
struct xfs_buf {TYPE_2__* b_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_DIR2_BLOCK_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_BLOCK_MAGIC ; 
 int /*<<< orphan*/  XFS_DIR3_DATA_MAGIC ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_dir2_data_unused_tag_p (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_trans_log_buf (int /*<<< orphan*/ ,struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_dir2_data_log_unused(
	struct xfs_da_args	*args,
	struct xfs_buf		*bp,
	xfs_dir2_data_unused_t	*dup)		/* data unused pointer */
{
	xfs_dir2_data_hdr_t	*hdr = bp->b_addr;

	ASSERT(hdr->magic == cpu_to_be32(XFS_DIR2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR3_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR2_BLOCK_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_DIR3_BLOCK_MAGIC));

	/*
	 * Log the first part of the unused entry.
	 */
	xfs_trans_log_buf(args->trans, bp, (uint)((char *)dup - (char *)hdr),
		(uint)((char *)&dup->length + sizeof(dup->length) -
		       1 - (char *)hdr));
	/*
	 * Log the end (tag) of the unused entry.
	 */
	xfs_trans_log_buf(args->trans, bp,
		(uint)((char *)xfs_dir2_data_unused_tag_p(dup) - (char *)hdr),
		(uint)((char *)xfs_dir2_data_unused_tag_p(dup) - (char *)hdr +
		       sizeof(xfs_dir2_data_off_t) - 1));
}