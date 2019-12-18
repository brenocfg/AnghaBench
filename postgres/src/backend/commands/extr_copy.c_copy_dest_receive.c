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
struct TYPE_2__ {int /*<<< orphan*/  processed; int /*<<< orphan*/  cstate; } ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_1__ DR_copy ;
typedef  int /*<<< orphan*/  CopyState ;

/* Variables and functions */
 int /*<<< orphan*/  CopyOneRowTo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
copy_dest_receive(TupleTableSlot *slot, DestReceiver *self)
{
	DR_copy    *myState = (DR_copy *) self;
	CopyState	cstate = myState->cstate;

	/* Send the data */
	CopyOneRowTo(cstate, slot);
	myState->processed++;

	return true;
}