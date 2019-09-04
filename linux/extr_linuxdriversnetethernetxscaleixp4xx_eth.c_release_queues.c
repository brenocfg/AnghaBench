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
struct port {TYPE_1__* plat; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  txreadyq; int /*<<< orphan*/  rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXFREE_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXDONE_QUEUE ; 
 int /*<<< orphan*/  TX_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ports_open ; 
 int /*<<< orphan*/  qmgr_release_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_queues(struct port *port)
{
	qmgr_release_queue(RXFREE_QUEUE(port->id));
	qmgr_release_queue(port->plat->rxq);
	qmgr_release_queue(TX_QUEUE(port->id));
	qmgr_release_queue(port->plat->txreadyq);

	if (!ports_open)
		qmgr_release_queue(TXDONE_QUEUE);
}