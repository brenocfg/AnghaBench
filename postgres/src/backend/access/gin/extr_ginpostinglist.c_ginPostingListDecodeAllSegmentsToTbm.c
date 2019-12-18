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
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  GinPostingList ;

/* Variables and functions */
 int /*<<< orphan*/  ginPostingListDecodeAllSegments (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbm_add_tuples (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

int
ginPostingListDecodeAllSegmentsToTbm(GinPostingList *ptr, int len,
									 TIDBitmap *tbm)
{
	int			ndecoded;
	ItemPointer items;

	items = ginPostingListDecodeAllSegments(ptr, len, &ndecoded);
	tbm_add_tuples(tbm, items, ndecoded, false);
	pfree(items);

	return ndecoded;
}