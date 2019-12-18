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
typedef  int uint ;
struct xfs_log_vec {int dummy; } ;
struct xfs_log_iovec {int dummy; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int XFS_BLF_CHUNK ; 
 int /*<<< orphan*/  XLOG_REG_TYPE_BCHUNK ; 
 int /*<<< orphan*/  xfs_buf_offset (struct xfs_buf*,int) ; 
 int /*<<< orphan*/  xlog_copy_iovec (struct xfs_log_vec*,struct xfs_log_iovec**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
xfs_buf_item_copy_iovec(
	struct xfs_log_vec	*lv,
	struct xfs_log_iovec	**vecp,
	struct xfs_buf		*bp,
	uint			offset,
	int			first_bit,
	uint			nbits)
{
	offset += first_bit * XFS_BLF_CHUNK;
	xlog_copy_iovec(lv, vecp, XLOG_REG_TYPE_BCHUNK,
			xfs_buf_offset(bp, offset),
			nbits * XFS_BLF_CHUNK);
}