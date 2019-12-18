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
typedef  int /*<<< orphan*/  xfs_bmdr_rec_t ;
typedef  int /*<<< orphan*/  xfs_bmdr_ptr_t ;
typedef  int /*<<< orphan*/  xfs_bmdr_key_t ;
typedef  int /*<<< orphan*/  xfs_bmdr_block_t ;

/* Variables and functions */

int
xfs_bmdr_maxrecs(
	int			blocklen,
	int			leaf)
{
	blocklen -= sizeof(xfs_bmdr_block_t);

	if (leaf)
		return blocklen / sizeof(xfs_bmdr_rec_t);
	return blocklen / (sizeof(xfs_bmdr_key_t) + sizeof(xfs_bmdr_ptr_t));
}