#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nitems; int /*<<< orphan*/  node; int /*<<< orphan*/ * items; int /*<<< orphan*/ * seg; int /*<<< orphan*/  action; } ;
typedef  TYPE_1__ leafSegmentInfo ;
struct TYPE_6__ {int oldformat; int /*<<< orphan*/  segments; } ;
typedef  TYPE_2__ disassembledLeaf ;
typedef  scalar_t__ Pointer ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  ItemPointerData ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  GinPostingList ;

/* Variables and functions */
 int /*<<< orphan*/  GIN_SEGMENT_REPLACE ; 
 int /*<<< orphan*/  GIN_SEGMENT_UNMODIFIED ; 
 int /*<<< orphan*/ * GinDataLeafPageGetPostingList (int /*<<< orphan*/ ) ; 
 scalar_t__ GinDataLeafPageGetPostingListSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GinNextPostingListSegment (int /*<<< orphan*/ *) ; 
 scalar_t__ GinPageIsCompressed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dataLeafPageGetUncompressed (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dlist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_push_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* palloc (int) ; 
 TYPE_2__* palloc0 (int) ; 

__attribute__((used)) static disassembledLeaf *
disassembleLeaf(Page page)
{
	disassembledLeaf *leaf;
	GinPostingList *seg;
	Pointer		segbegin;
	Pointer		segend;

	leaf = palloc0(sizeof(disassembledLeaf));
	dlist_init(&leaf->segments);

	if (GinPageIsCompressed(page))
	{
		/*
		 * Create a leafSegmentInfo entry for each segment.
		 */
		seg = GinDataLeafPageGetPostingList(page);
		segbegin = (Pointer) seg;
		segend = segbegin + GinDataLeafPageGetPostingListSize(page);
		while ((Pointer) seg < segend)
		{
			leafSegmentInfo *seginfo = palloc(sizeof(leafSegmentInfo));

			seginfo->action = GIN_SEGMENT_UNMODIFIED;
			seginfo->seg = seg;
			seginfo->items = NULL;
			seginfo->nitems = 0;
			dlist_push_tail(&leaf->segments, &seginfo->node);

			seg = GinNextPostingListSegment(seg);
		}
		leaf->oldformat = false;
	}
	else
	{
		/*
		 * A pre-9.4 format uncompressed page is represented by a single
		 * segment, with an array of items.  The corner case is uncompressed
		 * page containing no items, which is represented as no segments.
		 */
		ItemPointer uncompressed;
		int			nuncompressed;
		leafSegmentInfo *seginfo;

		uncompressed = dataLeafPageGetUncompressed(page, &nuncompressed);

		if (nuncompressed > 0)
		{
			seginfo = palloc(sizeof(leafSegmentInfo));

			seginfo->action = GIN_SEGMENT_REPLACE;
			seginfo->seg = NULL;
			seginfo->items = palloc(nuncompressed * sizeof(ItemPointerData));
			memcpy(seginfo->items, uncompressed, nuncompressed * sizeof(ItemPointerData));
			seginfo->nitems = nuncompressed;

			dlist_push_tail(&leaf->segments, &seginfo->node);
		}

		leaf->oldformat = true;
	}

	return leaf;
}