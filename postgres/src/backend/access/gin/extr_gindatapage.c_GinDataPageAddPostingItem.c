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
struct TYPE_2__ {scalar_t__ maxoff; } ;
typedef  int /*<<< orphan*/  PostingItem ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ GinDataPageGetPostingItem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GinDataPageSetDataSize (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* GinPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidBlockNumber ; 
 scalar_t__ InvalidOffsetNumber ; 
 scalar_t__ PostingItemGetBlockNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 

void
GinDataPageAddPostingItem(Page page, PostingItem *data, OffsetNumber offset)
{
	OffsetNumber maxoff = GinPageGetOpaque(page)->maxoff;
	char	   *ptr;

	Assert(PostingItemGetBlockNumber(data) != InvalidBlockNumber);
	Assert(!GinPageIsLeaf(page));

	if (offset == InvalidOffsetNumber)
	{
		ptr = (char *) GinDataPageGetPostingItem(page, maxoff + 1);
	}
	else
	{
		ptr = (char *) GinDataPageGetPostingItem(page, offset);
		if (offset != maxoff + 1)
			memmove(ptr + sizeof(PostingItem),
					ptr,
					(maxoff - offset + 1) * sizeof(PostingItem));
	}
	memcpy(ptr, data, sizeof(PostingItem));

	maxoff++;
	GinPageGetOpaque(page)->maxoff = maxoff;

	/*
	 * Also set pd_lower to the end of the posting items, to follow the
	 * "standard" page layout, so that we can squeeze out the unused space
	 * from full-page images.
	 */
	GinDataPageSetDataSize(page, maxoff * sizeof(PostingItem));
}