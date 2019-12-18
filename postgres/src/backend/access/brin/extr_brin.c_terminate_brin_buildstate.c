#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* bs_dtuple; int /*<<< orphan*/  bs_bdesc; int /*<<< orphan*/  bs_irel; int /*<<< orphan*/  bs_currentInsertBuf; } ;
typedef  int /*<<< orphan*/  Size ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_1__ BrinBuildState ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 scalar_t__ BufferGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BufferIsInvalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeSpaceMapVacuumRange (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PageGetFreeSpace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RecordPageWithFreeSpace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brin_free_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (TYPE_1__*) ; 

__attribute__((used)) static void
terminate_brin_buildstate(BrinBuildState *state)
{
	/*
	 * Release the last index buffer used.  We might as well ensure that
	 * whatever free space remains in that page is available in FSM, too.
	 */
	if (!BufferIsInvalid(state->bs_currentInsertBuf))
	{
		Page		page;
		Size		freespace;
		BlockNumber blk;

		page = BufferGetPage(state->bs_currentInsertBuf);
		freespace = PageGetFreeSpace(page);
		blk = BufferGetBlockNumber(state->bs_currentInsertBuf);
		ReleaseBuffer(state->bs_currentInsertBuf);
		RecordPageWithFreeSpace(state->bs_irel, blk, freespace);
		FreeSpaceMapVacuumRange(state->bs_irel, blk, blk + 1);
	}

	brin_free_desc(state->bs_bdesc);
	pfree(state->bs_dtuple);
	pfree(state);
}