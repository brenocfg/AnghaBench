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
struct port {size_t id; TYPE_1__* plat; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx; int /*<<< orphan*/  txdone; int /*<<< orphan*/  rx; int /*<<< orphan*/  rxfree; } ;
struct TYPE_3__ {int /*<<< orphan*/  txreadyq; } ;

/* Variables and functions */
 int /*<<< orphan*/  qmgr_release_queue (int /*<<< orphan*/ ) ; 
 TYPE_2__* queue_ids ; 

__attribute__((used)) static void release_hdlc_queues(struct port *port)
{
	qmgr_release_queue(queue_ids[port->id].rxfree);
	qmgr_release_queue(queue_ids[port->id].rx);
	qmgr_release_queue(queue_ids[port->id].txdone);
	qmgr_release_queue(queue_ids[port->id].tx);
	qmgr_release_queue(port->plat->txreadyq);
}