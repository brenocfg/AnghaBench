#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pd_lower; } ;
typedef  TYPE_1__* PageHeader ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 scalar_t__ SizeOfPageHeaderData ; 
 int /*<<< orphan*/  mask_page_hint_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_page_lsn_and_checksum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_unused_space (int /*<<< orphan*/ ) ; 

void
spg_mask(char *pagedata, BlockNumber blkno)
{
	Page		page = (Page) pagedata;
	PageHeader	pagehdr = (PageHeader) page;

	mask_page_lsn_and_checksum(page);

	mask_page_hint_bits(page);

	/*
	 * Mask the unused space, but only if the page's pd_lower appears to have
	 * been set correctly.
	 */
	if (pagehdr->pd_lower > SizeOfPageHeaderData)
		mask_unused_space(page);
}