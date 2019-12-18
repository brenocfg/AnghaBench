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
struct TYPE_2__ {int /*<<< orphan*/ * queue; } ;
typedef  TYPE_1__ TQueueDestReceiver ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_mq_detach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tqueueDestroyReceiver(DestReceiver *self)
{
	TQueueDestReceiver *tqueue = (TQueueDestReceiver *) self;

	/* We probably already detached from queue, but let's be sure */
	if (tqueue->queue != NULL)
		shm_mq_detach(tqueue->queue);
	pfree(self);
}