#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_10__ {int /*<<< orphan*/  t_info; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__* IndexTuple ;
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  GinGetPostingOffset (TYPE_1__*) ; 
 int /*<<< orphan*/  GinIsPostingTree (TYPE_1__*) ; 
 scalar_t__ GinPageIsLeaf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GinSetDownlink (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEX_SIZE_MASK ; 
 int /*<<< orphan*/  IndexTupleSize (TYPE_1__*) ; 
 int /*<<< orphan*/  MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static IndexTuple
GinFormInteriorTuple(IndexTuple itup, Page page, BlockNumber childblk)
{
	IndexTuple	nitup;

	if (GinPageIsLeaf(page) && !GinIsPostingTree(itup))
	{
		/* Tuple contains a posting list, just copy stuff before that */
		uint32		origsize = GinGetPostingOffset(itup);

		origsize = MAXALIGN(origsize);
		nitup = (IndexTuple) palloc(origsize);
		memcpy(nitup, itup, origsize);
		/* ... be sure to fix the size header field ... */
		nitup->t_info &= ~INDEX_SIZE_MASK;
		nitup->t_info |= origsize;
	}
	else
	{
		/* Copy the tuple as-is */
		nitup = (IndexTuple) palloc(IndexTupleSize(itup));
		memcpy(nitup, itup, IndexTupleSize(itup));
	}

	/* Now insert the correct downlink */
	GinSetDownlink(nitup, childblk);

	return nitup;
}