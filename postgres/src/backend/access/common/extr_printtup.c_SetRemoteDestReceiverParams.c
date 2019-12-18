#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mydest; int /*<<< orphan*/  receiveSlot; } ;
struct TYPE_7__ {TYPE_1__ pub; TYPE_2__* portal; } ;
struct TYPE_6__ {scalar_t__* formats; } ;
typedef  TYPE_2__* Portal ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_3__ DR_printtup ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DestRemote ; 
 scalar_t__ DestRemoteExecute ; 
 int /*<<< orphan*/  FrontendProtocol ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printtup_20 ; 
 int /*<<< orphan*/  printtup_internal_20 ; 

void
SetRemoteDestReceiverParams(DestReceiver *self, Portal portal)
{
	DR_printtup *myState = (DR_printtup *) self;

	Assert(myState->pub.mydest == DestRemote ||
		   myState->pub.mydest == DestRemoteExecute);

	myState->portal = portal;

	if (PG_PROTOCOL_MAJOR(FrontendProtocol) < 3)
	{
		/*
		 * In protocol 2.0 the Bind message does not exist, so there is no way
		 * for the columns to have different print formats; it's sufficient to
		 * look at the first one.
		 */
		if (portal->formats && portal->formats[0] != 0)
			myState->pub.receiveSlot = printtup_internal_20;
		else
			myState->pub.receiveSlot = printtup_20;
	}
}