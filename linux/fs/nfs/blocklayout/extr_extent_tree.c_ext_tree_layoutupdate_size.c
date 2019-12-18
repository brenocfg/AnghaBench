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
struct pnfs_block_layout {scalar_t__ bl_scsi_layout; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 size_t PNFS_BLOCK_EXTENT_SIZE ; 
 size_t PNFS_SCSI_RANGE_SIZE ; 

__attribute__((used)) static size_t ext_tree_layoutupdate_size(struct pnfs_block_layout *bl, size_t count)
{
	if (bl->bl_scsi_layout)
		return sizeof(__be32) + PNFS_SCSI_RANGE_SIZE * count;
	else
		return sizeof(__be32) + PNFS_BLOCK_EXTENT_SIZE * count;
}