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
typedef  int /*<<< orphan*/  TIDBitmap ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  GinPostingList ;

/* Variables and functions */
 int /*<<< orphan*/ * GinDataLeafPageGetPostingList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinDataLeafPageGetPostingListSize (int /*<<< orphan*/ ) ; 
 scalar_t__ GinPageIsCompressed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dataLeafPageGetUncompressed (int /*<<< orphan*/ ,int*) ; 
 int ginPostingListDecodeAllSegmentsToTbm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbm_add_tuples (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

int
GinDataLeafPageGetItemsToTbm(Page page, TIDBitmap *tbm)
{
	ItemPointer uncompressed;
	int			nitems;

	if (GinPageIsCompressed(page))
	{
		GinPostingList *segment = GinDataLeafPageGetPostingList(page);
		Size		len = GinDataLeafPageGetPostingListSize(page);

		nitems = ginPostingListDecodeAllSegmentsToTbm(segment, len, tbm);
	}
	else
	{
		uncompressed = dataLeafPageGetUncompressed(page, &nitems);

		if (nitems > 0)
			tbm_add_tuples(tbm, uncompressed, nitems, false);
	}

	return nitems;
}