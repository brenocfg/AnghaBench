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
struct TYPE_4__ {scalar_t__ processed; int /*<<< orphan*/ * cstate; TYPE_1__ pub; } ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_2__ DR_copy ;

/* Variables and functions */
 int /*<<< orphan*/  DestCopyOut ; 
 int /*<<< orphan*/  copy_dest_destroy ; 
 int /*<<< orphan*/  copy_dest_receive ; 
 int /*<<< orphan*/  copy_dest_shutdown ; 
 int /*<<< orphan*/  copy_dest_startup ; 
 scalar_t__ palloc (int) ; 

DestReceiver *
CreateCopyDestReceiver(void)
{
	DR_copy    *self = (DR_copy *) palloc(sizeof(DR_copy));

	self->pub.receiveSlot = copy_dest_receive;
	self->pub.rStartup = copy_dest_startup;
	self->pub.rShutdown = copy_dest_shutdown;
	self->pub.rDestroy = copy_dest_destroy;
	self->pub.mydest = DestCopyOut;

	self->cstate = NULL;		/* will be set later */
	self->processed = 0;

	return (DestReceiver *) self;
}