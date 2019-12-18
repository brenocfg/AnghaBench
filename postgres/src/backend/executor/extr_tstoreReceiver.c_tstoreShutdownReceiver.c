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
struct TYPE_2__ {int /*<<< orphan*/ * tofree; int /*<<< orphan*/ * outvalues; } ;
typedef  TYPE_1__ TStoreState ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tstoreShutdownReceiver(DestReceiver *self)
{
	TStoreState *myState = (TStoreState *) self;

	/* Release workspace if any */
	if (myState->outvalues)
		pfree(myState->outvalues);
	myState->outvalues = NULL;
	if (myState->tofree)
		pfree(myState->tofree);
	myState->tofree = NULL;
}