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
typedef  int /*<<< orphan*/  xfs_rmap_ptr_t ;
struct xfs_rmap_rec {int dummy; } ;
struct xfs_rmap_key {int dummy; } ;

/* Variables and functions */
 scalar_t__ XFS_RMAP_BLOCK_LEN ; 

int
xfs_rmapbt_maxrecs(
	int			blocklen,
	int			leaf)
{
	blocklen -= XFS_RMAP_BLOCK_LEN;

	if (leaf)
		return blocklen / sizeof(struct xfs_rmap_rec);
	return blocklen /
		(2 * sizeof(struct xfs_rmap_key) + sizeof(xfs_rmap_ptr_t));
}