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
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_2__ {int /*<<< orphan*/  tstore; int /*<<< orphan*/  filter; } ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_1__ DR_sqlfunction ;

/* Variables and functions */
 int /*<<< orphan*/ * ExecFilterJunk (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_puttupleslot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
sqlfunction_receive(TupleTableSlot *slot, DestReceiver *self)
{
	DR_sqlfunction *myState = (DR_sqlfunction *) self;

	/* Filter tuple as needed */
	slot = ExecFilterJunk(myState->filter, slot);

	/* Store the filtered tuple into the tuplestore */
	tuplestore_puttupleslot(myState->tstore, slot);

	return true;
}