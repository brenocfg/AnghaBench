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
struct TYPE_4__ {int /*<<< orphan*/  transientoid; TYPE_1__ pub; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_2__ DR_transientrel ;

/* Variables and functions */
 int /*<<< orphan*/  DestTransientRel ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  transientrel_destroy ; 
 int /*<<< orphan*/  transientrel_receive ; 
 int /*<<< orphan*/  transientrel_shutdown ; 
 int /*<<< orphan*/  transientrel_startup ; 

DestReceiver *
CreateTransientRelDestReceiver(Oid transientoid)
{
	DR_transientrel *self = (DR_transientrel *) palloc0(sizeof(DR_transientrel));

	self->pub.receiveSlot = transientrel_receive;
	self->pub.rStartup = transientrel_startup;
	self->pub.rShutdown = transientrel_shutdown;
	self->pub.rDestroy = transientrel_destroy;
	self->pub.mydest = DestTransientRel;
	self->transientoid = transientoid;

	return (DestReceiver *) self;
}