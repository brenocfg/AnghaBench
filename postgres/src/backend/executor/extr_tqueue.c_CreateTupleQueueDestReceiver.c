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
typedef  int /*<<< orphan*/  shm_mq_handle ;
struct TYPE_3__ {int /*<<< orphan*/  mydest; int /*<<< orphan*/  rDestroy; int /*<<< orphan*/  rShutdown; int /*<<< orphan*/  rStartup; int /*<<< orphan*/  receiveSlot; } ;
struct TYPE_4__ {int /*<<< orphan*/ * queue; TYPE_1__ pub; } ;
typedef  TYPE_2__ TQueueDestReceiver ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  DestTupleQueue ; 
 scalar_t__ palloc0 (int) ; 
 int /*<<< orphan*/  tqueueDestroyReceiver ; 
 int /*<<< orphan*/  tqueueReceiveSlot ; 
 int /*<<< orphan*/  tqueueShutdownReceiver ; 
 int /*<<< orphan*/  tqueueStartupReceiver ; 

DestReceiver *
CreateTupleQueueDestReceiver(shm_mq_handle *handle)
{
	TQueueDestReceiver *self;

	self = (TQueueDestReceiver *) palloc0(sizeof(TQueueDestReceiver));

	self->pub.receiveSlot = tqueueReceiveSlot;
	self->pub.rStartup = tqueueStartupReceiver;
	self->pub.rShutdown = tqueueShutdownReceiver;
	self->pub.rDestroy = tqueueDestroyReceiver;
	self->pub.mydest = DestTupleQueue;
	self->queue = handle;

	return (DestReceiver *) self;
}