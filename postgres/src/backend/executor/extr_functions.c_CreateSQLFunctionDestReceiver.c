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
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_2__ DR_sqlfunction ;

/* Variables and functions */
 int /*<<< orphan*/  DestSQLFunction ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  sqlfunction_destroy ; 
 int /*<<< orphan*/  sqlfunction_receive ; 
 int /*<<< orphan*/  sqlfunction_shutdown ; 
 int /*<<< orphan*/  sqlfunction_startup ; 

DestReceiver *
CreateSQLFunctionDestReceiver(void)
{
	DR_sqlfunction *self = (DR_sqlfunction *) palloc0(sizeof(DR_sqlfunction));

	self->pub.receiveSlot = sqlfunction_receive;
	self->pub.rStartup = sqlfunction_startup;
	self->pub.rShutdown = sqlfunction_shutdown;
	self->pub.rDestroy = sqlfunction_destroy;
	self->pub.mydest = DestSQLFunction;

	/* private fields will be set by postquel_start */

	return (DestReceiver *) self;
}