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
struct pnfs_layout_range {int iomode; scalar_t__ offset; scalar_t__ length; } ;

/* Variables and functions */
#define  IOMODE_READ 129 
#define  IOMODE_RW 128 
 scalar_t__ NFS4_MAX_UINT64 ; 

__attribute__((used)) static bool
pnfs_sanity_check_layout_range(struct pnfs_layout_range *range)
{
	switch (range->iomode) {
	case IOMODE_READ:
	case IOMODE_RW:
		break;
	default:
		return false;
	}
	if (range->offset == NFS4_MAX_UINT64)
		return false;
	if (range->length == 0)
		return false;
	if (range->length != NFS4_MAX_UINT64 &&
	    range->length > NFS4_MAX_UINT64 - range->offset)
		return false;
	return true;
}