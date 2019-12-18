#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {scalar_t__ pd_lower; } ;
typedef  TYPE_1__* PageHeader ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_2__* GinPageOpaque ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int GIN_DELETED ; 
 TYPE_2__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 scalar_t__ SizeOfPageHeaderData ; 
 int /*<<< orphan*/  mask_page_content (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_page_hint_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_page_lsn_and_checksum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_unused_space (int /*<<< orphan*/ ) ; 

void
gin_mask(char *pagedata, BlockNumber blkno)
{
	Page		page = (Page) pagedata;
	PageHeader	pagehdr = (PageHeader) page;
	GinPageOpaque opaque;

	mask_page_lsn_and_checksum(page);
	opaque = GinPageGetOpaque(page);

	mask_page_hint_bits(page);

	/*
	 * For a GIN_DELETED page, the page is initialized to empty.  Hence, mask
	 * the whole page content.  For other pages, mask the hole if pd_lower
	 * appears to have been set correctly.
	 */
	if (opaque->flags & GIN_DELETED)
		mask_page_content(page);
	else if (pagehdr->pd_lower > SizeOfPageHeaderData)
		mask_unused_space(page);
}