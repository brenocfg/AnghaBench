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
typedef  int /*<<< orphan*/  xfs_refcount_ptr_t ;
struct xfs_refcount_rec {int dummy; } ;
struct xfs_refcount_key {int dummy; } ;

/* Variables and functions */
 scalar_t__ XFS_REFCOUNT_BLOCK_LEN ; 

int
xfs_refcountbt_maxrecs(
	int			blocklen,
	bool			leaf)
{
	blocklen -= XFS_REFCOUNT_BLOCK_LEN;

	if (leaf)
		return blocklen / sizeof(struct xfs_refcount_rec);
	return blocklen / (sizeof(struct xfs_refcount_key) +
			   sizeof(xfs_refcount_ptr_t));
}