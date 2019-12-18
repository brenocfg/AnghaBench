#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rel; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  int /*<<< orphan*/  ItemId ;
typedef  TYPE_1__ BtreeCheckState ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  int /*<<< orphan*/  BTPageOpaqueData ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  ERRCODE_INDEX_CORRUPTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ItemIdGetFlags (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdGetLength (int /*<<< orphan*/ ) ; 
 int ItemIdGetOffset (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemIdIsRedirected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemIdIsUsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageGetItemId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ItemId
PageGetItemIdCareful(BtreeCheckState *state, BlockNumber block, Page page,
					 OffsetNumber offset)
{
	ItemId		itemid = PageGetItemId(page, offset);

	if (ItemIdGetOffset(itemid) + ItemIdGetLength(itemid) >
		BLCKSZ - sizeof(BTPageOpaqueData))
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg("line pointer points past end of tuple space in index \"%s\"",
						RelationGetRelationName(state->rel)),
				 errdetail_internal("Index tid=(%u,%u) lp_off=%u, lp_len=%u lp_flags=%u.",
									block, offset, ItemIdGetOffset(itemid),
									ItemIdGetLength(itemid),
									ItemIdGetFlags(itemid))));

	/*
	 * Verify that line pointer isn't LP_REDIRECT or LP_UNUSED, since nbtree
	 * never uses either.  Verify that line pointer has storage, too, since
	 * even LP_DEAD items should within nbtree.
	 */
	if (ItemIdIsRedirected(itemid) || !ItemIdIsUsed(itemid) ||
		ItemIdGetLength(itemid) == 0)
		ereport(ERROR,
				(errcode(ERRCODE_INDEX_CORRUPTED),
				 errmsg("invalid line pointer storage in index \"%s\"",
						RelationGetRelationName(state->rel)),
				 errdetail_internal("Index tid=(%u,%u) lp_off=%u, lp_len=%u lp_flags=%u.",
									block, offset, ItemIdGetOffset(itemid),
									ItemIdGetLength(itemid),
									ItemIdGetFlags(itemid))));

	return itemid;
}