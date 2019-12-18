#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nPlaceholder; } ;
struct TYPE_3__ {scalar_t__ tupstate; } ;
typedef  TYPE_1__* SpGistDeadTuple ;
typedef  int /*<<< orphan*/  Page ;
typedef  scalar_t__ OffsetNumber ;
typedef  int /*<<< orphan*/  Item ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PageAddItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  PageGetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PageGetMaxOffsetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageIndexTupleDelete (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SPGIST_PLACEHOLDER ; 
 TYPE_2__* SpGistPageGetOpaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
addOrReplaceTuple(Page page, Item tuple, int size, OffsetNumber offset)
{
	if (offset <= PageGetMaxOffsetNumber(page))
	{
		SpGistDeadTuple dt = (SpGistDeadTuple) PageGetItem(page,
														   PageGetItemId(page, offset));

		if (dt->tupstate != SPGIST_PLACEHOLDER)
			elog(ERROR, "SPGiST tuple to be replaced is not a placeholder");

		Assert(SpGistPageGetOpaque(page)->nPlaceholder > 0);
		SpGistPageGetOpaque(page)->nPlaceholder--;

		PageIndexTupleDelete(page, offset);
	}

	Assert(offset <= PageGetMaxOffsetNumber(page) + 1);

	if (PageAddItem(page, tuple, size, offset, false, false) != offset)
		elog(ERROR, "failed to add item of size %u to SPGiST index page",
			 size);
}