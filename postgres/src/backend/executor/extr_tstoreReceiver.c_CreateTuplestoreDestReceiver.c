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
struct TYPE_3__ {int /*<<< orphan*/  mydest; int /*<<< orphan*/  rDestroy; int /*<<< orphan*/  rShutdown; int /*<<< orphan*/  rStartup; int /*<<< orphan*/  receiveSlot; } ;
struct TYPE_4__ {TYPE_1__ pub; } ;
typedef  TYPE_2__ TStoreState ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  DestTuplestore ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  tstoreDestroyReceiver ; 
 int /*<<< orphan*/  tstoreReceiveSlot_notoast ; 
 int /*<<< orphan*/  tstoreShutdownReceiver ; 
 int /*<<< orphan*/  tstoreStartupReceiver ; 

DestReceiver *
CreateTuplestoreDestReceiver(void)
{
	TStoreState *self = (TStoreState *) palloc0(sizeof(TStoreState));

	self->pub.receiveSlot = tstoreReceiveSlot_notoast;	/* might change */
	self->pub.rStartup = tstoreStartupReceiver;
	self->pub.rShutdown = tstoreShutdownReceiver;
	self->pub.rDestroy = tstoreDestroyReceiver;
	self->pub.mydest = DestTuplestore;

	/* private fields will be set by SetTuplestoreDestReceiverParams */

	return (DestReceiver *) self;
}