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
typedef  scalar_t__ uint ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 scalar_t__ XFS_BLF_CHUNK ; 
 int XFS_BLF_SHIFT ; 
 scalar_t__ xfs_buf_offset (struct xfs_buf*,scalar_t__) ; 

__attribute__((used)) static inline bool
xfs_buf_item_straddle(
	struct xfs_buf		*bp,
	uint			offset,
	int			next_bit,
	int			last_bit)
{
	return xfs_buf_offset(bp, offset + (next_bit << XFS_BLF_SHIFT)) !=
		(xfs_buf_offset(bp, offset + (last_bit << XFS_BLF_SHIFT)) +
		 XFS_BLF_CHUNK);
}