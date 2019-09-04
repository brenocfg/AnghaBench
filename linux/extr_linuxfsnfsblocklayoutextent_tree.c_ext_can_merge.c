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
struct pnfs_block_extent {scalar_t__ be_state; scalar_t__ be_device; scalar_t__ be_f_offset; scalar_t__ be_length; scalar_t__ be_v_offset; scalar_t__ be_tag; } ;

/* Variables and functions */
 scalar_t__ PNFS_BLOCK_INVALID_DATA ; 
 scalar_t__ PNFS_BLOCK_NONE_DATA ; 

__attribute__((used)) static bool
ext_can_merge(struct pnfs_block_extent *be1, struct pnfs_block_extent *be2)
{
	if (be1->be_state != be2->be_state)
		return false;
	if (be1->be_device != be2->be_device)
		return false;

	if (be1->be_f_offset + be1->be_length != be2->be_f_offset)
		return false;

	if (be1->be_state != PNFS_BLOCK_NONE_DATA &&
	    (be1->be_v_offset + be1->be_length != be2->be_v_offset))
		return false;

	if (be1->be_state == PNFS_BLOCK_INVALID_DATA &&
	    be1->be_tag != be2->be_tag)
		return false;

	return true;
}