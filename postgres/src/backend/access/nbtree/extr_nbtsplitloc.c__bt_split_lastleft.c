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
struct TYPE_6__ {scalar_t__ newitemoff; int /*<<< orphan*/  page; int /*<<< orphan*/  newitem; } ;
struct TYPE_5__ {scalar_t__ firstoldonright; scalar_t__ newitemonleft; } ;
typedef  TYPE_1__ SplitPoint ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  int /*<<< orphan*/  IndexTuple ;
typedef  TYPE_2__ FindSplitData ;

/* Variables and functions */
 int /*<<< orphan*/  OffsetNumberPrev (scalar_t__) ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline IndexTuple
_bt_split_lastleft(FindSplitData *state, SplitPoint *split)
{
	ItemId		itemid;

	if (split->newitemonleft && split->firstoldonright == state->newitemoff)
		return state->newitem;

	itemid = PageGetItemId(state->page,
						   OffsetNumberPrev(split->firstoldonright));
	return (IndexTuple) PageGetItem(state->page, itemid);
}