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
struct pnfs_block_extent {int be_state; int /*<<< orphan*/  be_tag; } ;

/* Variables and functions */
#define  PNFS_BLOCK_INVALID_DATA 129 
#define  PNFS_BLOCK_NONE_DATA 128 

__attribute__((used)) static bool is_hole(struct pnfs_block_extent *be)
{
	switch (be->be_state) {
	case PNFS_BLOCK_NONE_DATA:
		return true;
	case PNFS_BLOCK_INVALID_DATA:
		return be->be_tag ? false : true;
	default:
		return false;
	}
}