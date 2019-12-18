#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_9__ {int /*<<< orphan*/  (* rShutdown ) (TYPE_2__*) ;int /*<<< orphan*/  (* receiveSlot ) (int /*<<< orphan*/ *,TYPE_2__*) ;int /*<<< orphan*/  (* rStartup ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  holdStore; int /*<<< orphan*/  holdContext; int /*<<< orphan*/  tupDesc; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_1__* Portal ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SELECT ; 
 int /*<<< orphan*/  ExecClearTuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecDropSingleTupleTableSlot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MakeSingleTupleTableSlot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int ScanDirectionIsForward (int /*<<< orphan*/ ) ; 
 scalar_t__ ScanDirectionIsNoMovement (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTSOpsMinimalTuple ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 
 int tuplestore_gettupleslot (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64
RunFromStore(Portal portal, ScanDirection direction, uint64 count,
			 DestReceiver *dest)
{
	uint64		current_tuple_count = 0;
	TupleTableSlot *slot;

	slot = MakeSingleTupleTableSlot(portal->tupDesc, &TTSOpsMinimalTuple);

	dest->rStartup(dest, CMD_SELECT, portal->tupDesc);

	if (ScanDirectionIsNoMovement(direction))
	{
		/* do nothing except start/stop the destination */
	}
	else
	{
		bool		forward = ScanDirectionIsForward(direction);

		for (;;)
		{
			MemoryContext oldcontext;
			bool		ok;

			oldcontext = MemoryContextSwitchTo(portal->holdContext);

			ok = tuplestore_gettupleslot(portal->holdStore, forward, false,
										 slot);

			MemoryContextSwitchTo(oldcontext);

			if (!ok)
				break;

			/*
			 * If we are not able to send the tuple, we assume the destination
			 * has closed and no more tuples can be sent. If that's the case,
			 * end the loop.
			 */
			if (!dest->receiveSlot(slot, dest))
				break;

			ExecClearTuple(slot);

			/*
			 * check our tuple count.. if we've processed the proper number
			 * then quit, else loop again and process more tuples. Zero count
			 * means no limit.
			 */
			current_tuple_count++;
			if (count && count == current_tuple_count)
				break;
		}
	}

	dest->rShutdown(dest);

	ExecDropSingleTupleTableSlot(slot);

	return current_tuple_count;
}