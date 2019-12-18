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
struct TYPE_4__ {int /*<<< orphan*/ * into; TYPE_1__ pub; } ;
typedef  int /*<<< orphan*/  IntoClause ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_2__ DR_intorel ;

/* Variables and functions */
 int /*<<< orphan*/  DestIntoRel ; 
 int /*<<< orphan*/  intorel_destroy ; 
 int /*<<< orphan*/  intorel_receive ; 
 int /*<<< orphan*/  intorel_shutdown ; 
 int /*<<< orphan*/  intorel_startup ; 
 scalar_t__ palloc0 (int) ; 

DestReceiver *
CreateIntoRelDestReceiver(IntoClause *intoClause)
{
	DR_intorel *self = (DR_intorel *) palloc0(sizeof(DR_intorel));

	self->pub.receiveSlot = intorel_receive;
	self->pub.rStartup = intorel_startup;
	self->pub.rShutdown = intorel_shutdown;
	self->pub.rDestroy = intorel_destroy;
	self->pub.mydest = DestIntoRel;
	self->into = intoClause;
	/* other private fields will be set during intorel_startup */

	return (DestReceiver *) self;
}