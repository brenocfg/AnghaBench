#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ newitemoff; int newitemsz; int /*<<< orphan*/  rel; int /*<<< orphan*/  page; int /*<<< orphan*/  is_leaf; } ;
struct TYPE_9__ {scalar_t__ firstoldonright; int /*<<< orphan*/  newitemonleft; } ;
typedef  TYPE_1__ SplitPoint ;
typedef  int /*<<< orphan*/  ItemIdData ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  scalar_t__ IndexTuple ;
typedef  TYPE_2__ FindSplitData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int MAXALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 int _bt_keep_natts_fast (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ _bt_split_firstright (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ _bt_split_lastleft (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static inline int
_bt_split_penalty(FindSplitData *state, SplitPoint *split)
{
	IndexTuple	lastleftuple;
	IndexTuple	firstrighttuple;

	if (!state->is_leaf)
	{
		ItemId		itemid;

		if (!split->newitemonleft &&
			split->firstoldonright == state->newitemoff)
			return state->newitemsz;

		itemid = PageGetItemId(state->page, split->firstoldonright);

		return MAXALIGN(ItemIdGetLength(itemid)) + sizeof(ItemIdData);
	}

	lastleftuple = _bt_split_lastleft(state, split);
	firstrighttuple = _bt_split_firstright(state, split);

	Assert(lastleftuple != firstrighttuple);
	return _bt_keep_natts_fast(state->rel, lastleftuple, firstrighttuple);
}