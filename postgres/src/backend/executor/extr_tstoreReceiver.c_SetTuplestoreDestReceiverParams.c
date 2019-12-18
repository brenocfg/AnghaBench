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
typedef  int /*<<< orphan*/  Tuplestorestate ;
struct TYPE_3__ {scalar_t__ mydest; } ;
struct TYPE_4__ {int detoast; int /*<<< orphan*/  cxt; int /*<<< orphan*/ * tstore; TYPE_1__ pub; } ;
typedef  TYPE_2__ TStoreState ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DestTuplestore ; 

void
SetTuplestoreDestReceiverParams(DestReceiver *self,
								Tuplestorestate *tStore,
								MemoryContext tContext,
								bool detoast)
{
	TStoreState *myState = (TStoreState *) self;

	Assert(myState->pub.mydest == DestTuplestore);
	myState->tstore = tStore;
	myState->cxt = tContext;
	myState->detoast = detoast;
}