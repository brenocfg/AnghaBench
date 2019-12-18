#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_2__ {int ti_options; int /*<<< orphan*/  bistate; int /*<<< orphan*/  output_cid; int /*<<< orphan*/  transientrel; int /*<<< orphan*/  transientoid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_1__ DR_transientrel ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  GetBulkInsertState () ; 
 int /*<<< orphan*/  GetCurrentCommandId (int) ; 
 scalar_t__ InvalidBlockNumber ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ RelationGetTargetBlock (int /*<<< orphan*/ ) ; 
 int TABLE_INSERT_FROZEN ; 
 int TABLE_INSERT_SKIP_FSM ; 
 int TABLE_INSERT_SKIP_WAL ; 
 int /*<<< orphan*/  XLogIsNeeded () ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
transientrel_startup(DestReceiver *self, int operation, TupleDesc typeinfo)
{
	DR_transientrel *myState = (DR_transientrel *) self;
	Relation	transientrel;

	transientrel = table_open(myState->transientoid, NoLock);

	/*
	 * Fill private fields of myState for use by later routines
	 */
	myState->transientrel = transientrel;
	myState->output_cid = GetCurrentCommandId(true);

	/*
	 * We can skip WAL-logging the insertions, unless PITR or streaming
	 * replication is in use. We can skip the FSM in any case.
	 */
	myState->ti_options = TABLE_INSERT_SKIP_FSM | TABLE_INSERT_FROZEN;
	if (!XLogIsNeeded())
		myState->ti_options |= TABLE_INSERT_SKIP_WAL;
	myState->bistate = GetBulkInsertState();

	/* Not using WAL requires smgr_targblock be initially invalid */
	Assert(RelationGetTargetBlock(transientrel) == InvalidBlockNumber);
}