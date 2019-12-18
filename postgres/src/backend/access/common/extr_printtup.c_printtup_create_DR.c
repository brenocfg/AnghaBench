#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {scalar_t__ mydest; int /*<<< orphan*/  rDestroy; int /*<<< orphan*/  rShutdown; int /*<<< orphan*/  rStartup; int /*<<< orphan*/  receiveSlot; } ;
struct TYPE_6__ {int sendDescrip; int /*<<< orphan*/ * tmpcontext; TYPE_2__ buf; int /*<<< orphan*/ * myinfo; scalar_t__ nattrs; int /*<<< orphan*/ * attrinfo; TYPE_1__ pub; } ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  TYPE_3__ DR_printtup ;
typedef  scalar_t__ CommandDest ;

/* Variables and functions */
 scalar_t__ DestRemote ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  printtup ; 
 int /*<<< orphan*/  printtup_destroy ; 
 int /*<<< orphan*/  printtup_shutdown ; 
 int /*<<< orphan*/  printtup_startup ; 

DestReceiver *
printtup_create_DR(CommandDest dest)
{
	DR_printtup *self = (DR_printtup *) palloc0(sizeof(DR_printtup));

	self->pub.receiveSlot = printtup;	/* might get changed later */
	self->pub.rStartup = printtup_startup;
	self->pub.rShutdown = printtup_shutdown;
	self->pub.rDestroy = printtup_destroy;
	self->pub.mydest = dest;

	/*
	 * Send T message automatically if DestRemote, but not if
	 * DestRemoteExecute
	 */
	self->sendDescrip = (dest == DestRemote);

	self->attrinfo = NULL;
	self->nattrs = 0;
	self->myinfo = NULL;
	self->buf.data = NULL;
	self->tmpcontext = NULL;

	return (DestReceiver *) self;
}