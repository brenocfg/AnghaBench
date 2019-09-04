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
struct net_device {int dummy; } ;
struct cpsw_slave {scalar_t__ ndev; } ;
struct TYPE_2__ {int slaves; } ;
struct cpsw_common {int /*<<< orphan*/  dma; struct cpsw_slave* slaves; TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpdma_ctlr_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_intr_disable (struct cpsw_common*) ; 
 struct cpsw_common* ndev_to_cpsw (struct net_device*) ; 
 int /*<<< orphan*/  netif_dormant_on (scalar_t__) ; 
 scalar_t__ netif_running (scalar_t__) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (scalar_t__) ; 

__attribute__((used)) static void cpsw_suspend_data_pass(struct net_device *ndev)
{
	struct cpsw_common *cpsw = ndev_to_cpsw(ndev);
	struct cpsw_slave *slave;
	int i;

	/* Disable NAPI scheduling */
	cpsw_intr_disable(cpsw);

	/* Stop all transmit queues for every network device.
	 * Disable re-using rx descriptors with dormant_on.
	 */
	for (i = cpsw->data.slaves, slave = cpsw->slaves; i; i--, slave++) {
		if (!(slave->ndev && netif_running(slave->ndev)))
			continue;

		netif_tx_stop_all_queues(slave->ndev);
		netif_dormant_on(slave->ndev);
	}

	/* Handle rest of tx packets and stop cpdma channels */
	cpdma_ctlr_stop(cpsw->dma);
}