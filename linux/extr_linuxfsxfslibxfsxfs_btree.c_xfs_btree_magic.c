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
typedef  size_t xfs_btnum_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__** xfs_magics ; 

uint32_t
xfs_btree_magic(
	int			crc,
	xfs_btnum_t		btnum)
{
	uint32_t		magic = xfs_magics[crc][btnum];

	/* Ensure we asked for crc for crc-only magics. */
	ASSERT(magic != 0);
	return magic;
}