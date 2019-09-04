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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ id; int /*<<< orphan*/  dma_addr; } ;
struct il_tx_queue {int /*<<< orphan*/ * skbs; TYPE_3__ q; int /*<<< orphan*/  tfds; } ;
struct TYPE_5__ {size_t tfd_size; } ;
struct il_priv {scalar_t__ cmd_queue; TYPE_2__ hw_params; TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 size_t TFD_QUEUE_SIZE_MAX ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
il_tx_queue_alloc(struct il_priv *il, struct il_tx_queue *txq, u32 id)
{
	struct device *dev = &il->pci_dev->dev;
	size_t tfd_sz = il->hw_params.tfd_size * TFD_QUEUE_SIZE_MAX;

	/* Driver ilate data, only for Tx (not command) queues,
	 * not shared with device. */
	if (id != il->cmd_queue) {
		txq->skbs = kcalloc(TFD_QUEUE_SIZE_MAX,
				    sizeof(struct sk_buff *),
				    GFP_KERNEL);
		if (!txq->skbs) {
			IL_ERR("Fail to alloc skbs\n");
			goto error;
		}
	} else
		txq->skbs = NULL;

	/* Circular buffer of transmit frame descriptors (TFDs),
	 * shared with device */
	txq->tfds =
	    dma_alloc_coherent(dev, tfd_sz, &txq->q.dma_addr, GFP_KERNEL);
	if (!txq->tfds)
		goto error;

	txq->q.id = id;

	return 0;

error:
	kfree(txq->skbs);
	txq->skbs = NULL;

	return -ENOMEM;
}