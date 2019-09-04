#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ intr_idx; } ;
struct vmxnet3_rx_queue {int qid; int qid2; int dataRingQid; TYPE_4__ comp_ring; } ;
struct vmxnet3_intr {int num_intrs; scalar_t__ type; int /*<<< orphan*/  mask_mode; scalar_t__ event_intr_idx; int /*<<< orphan*/ * mod_levels; } ;
struct vmxnet3_adapter {int num_rx_queues; int num_tx_queues; TYPE_5__* netdev; struct vmxnet3_rx_queue* rx_queue; TYPE_3__* tx_queue; struct vmxnet3_intr intr; TYPE_1__* pdev; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {scalar_t__ intr_idx; } ;
struct TYPE_10__ {TYPE_2__ comp_ring; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  UPT1_IML_ADAPTIVE ; 
 scalar_t__ VMXNET3_IT_MSIX ; 
 int /*<<< orphan*/  netdev_err (TYPE_5__*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  netdev_info (TYPE_5__*,char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  vmxnet3_intr ; 

__attribute__((used)) static int
vmxnet3_request_irqs(struct vmxnet3_adapter *adapter)
{
	struct vmxnet3_intr *intr = &adapter->intr;
	int err = 0, i;
	int vector = 0;

#ifdef CONFIG_PCI_MSI
	if (adapter->intr.type == VMXNET3_IT_MSIX) {
		for (i = 0; i < adapter->num_tx_queues; i++) {
			if (adapter->share_intr != VMXNET3_INTR_BUDDYSHARE) {
				sprintf(adapter->tx_queue[i].name, "%s-tx-%d",
					adapter->netdev->name, vector);
				err = request_irq(
					      intr->msix_entries[vector].vector,
					      vmxnet3_msix_tx, 0,
					      adapter->tx_queue[i].name,
					      &adapter->tx_queue[i]);
			} else {
				sprintf(adapter->tx_queue[i].name, "%s-rxtx-%d",
					adapter->netdev->name, vector);
			}
			if (err) {
				dev_err(&adapter->netdev->dev,
					"Failed to request irq for MSIX, %s, "
					"error %d\n",
					adapter->tx_queue[i].name, err);
				return err;
			}

			/* Handle the case where only 1 MSIx was allocated for
			 * all tx queues */
			if (adapter->share_intr == VMXNET3_INTR_TXSHARE) {
				for (; i < adapter->num_tx_queues; i++)
					adapter->tx_queue[i].comp_ring.intr_idx
								= vector;
				vector++;
				break;
			} else {
				adapter->tx_queue[i].comp_ring.intr_idx
								= vector++;
			}
		}
		if (adapter->share_intr == VMXNET3_INTR_BUDDYSHARE)
			vector = 0;

		for (i = 0; i < adapter->num_rx_queues; i++) {
			if (adapter->share_intr != VMXNET3_INTR_BUDDYSHARE)
				sprintf(adapter->rx_queue[i].name, "%s-rx-%d",
					adapter->netdev->name, vector);
			else
				sprintf(adapter->rx_queue[i].name, "%s-rxtx-%d",
					adapter->netdev->name, vector);
			err = request_irq(intr->msix_entries[vector].vector,
					  vmxnet3_msix_rx, 0,
					  adapter->rx_queue[i].name,
					  &(adapter->rx_queue[i]));
			if (err) {
				netdev_err(adapter->netdev,
					   "Failed to request irq for MSIX, "
					   "%s, error %d\n",
					   adapter->rx_queue[i].name, err);
				return err;
			}

			adapter->rx_queue[i].comp_ring.intr_idx = vector++;
		}

		sprintf(intr->event_msi_vector_name, "%s-event-%d",
			adapter->netdev->name, vector);
		err = request_irq(intr->msix_entries[vector].vector,
				  vmxnet3_msix_event, 0,
				  intr->event_msi_vector_name, adapter->netdev);
		intr->event_intr_idx = vector;

	} else if (intr->type == VMXNET3_IT_MSI) {
		adapter->num_rx_queues = 1;
		err = request_irq(adapter->pdev->irq, vmxnet3_intr, 0,
				  adapter->netdev->name, adapter->netdev);
	} else {
#endif
		adapter->num_rx_queues = 1;
		err = request_irq(adapter->pdev->irq, vmxnet3_intr,
				  IRQF_SHARED, adapter->netdev->name,
				  adapter->netdev);
#ifdef CONFIG_PCI_MSI
	}
#endif
	intr->num_intrs = vector + 1;
	if (err) {
		netdev_err(adapter->netdev,
			   "Failed to request irq (intr type:%d), error %d\n",
			   intr->type, err);
	} else {
		/* Number of rx queues will not change after this */
		for (i = 0; i < adapter->num_rx_queues; i++) {
			struct vmxnet3_rx_queue *rq = &adapter->rx_queue[i];
			rq->qid = i;
			rq->qid2 = i + adapter->num_rx_queues;
			rq->dataRingQid = i + 2 * adapter->num_rx_queues;
		}

		/* init our intr settings */
		for (i = 0; i < intr->num_intrs; i++)
			intr->mod_levels[i] = UPT1_IML_ADAPTIVE;
		if (adapter->intr.type != VMXNET3_IT_MSIX) {
			adapter->intr.event_intr_idx = 0;
			for (i = 0; i < adapter->num_tx_queues; i++)
				adapter->tx_queue[i].comp_ring.intr_idx = 0;
			adapter->rx_queue[0].comp_ring.intr_idx = 0;
		}

		netdev_info(adapter->netdev,
			    "intr type %u, mode %u, %u vectors allocated\n",
			    intr->type, intr->mask_mode, intr->num_intrs);
	}

	return err;
}