#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ntb_transport_qp {int /*<<< orphan*/  rx_memcpy; int /*<<< orphan*/  rx_async; struct dma_chan* rx_dma_chan; } ;
struct ntb_queue_entry {scalar_t__ len; int /*<<< orphan*/  retries; struct ntb_transport_qp* qp; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ copy_bytes ; 
 int ntb_async_rx_submit (struct ntb_queue_entry*,void*) ; 
 int /*<<< orphan*/  ntb_memcpy_rx (struct ntb_queue_entry*,void*) ; 

__attribute__((used)) static void ntb_async_rx(struct ntb_queue_entry *entry, void *offset)
{
	struct ntb_transport_qp *qp = entry->qp;
	struct dma_chan *chan = qp->rx_dma_chan;
	int res;

	if (!chan)
		goto err;

	if (entry->len < copy_bytes)
		goto err;

	res = ntb_async_rx_submit(entry, offset);
	if (res < 0)
		goto err;

	if (!entry->retries)
		qp->rx_async++;

	return;

err:
	ntb_memcpy_rx(entry, offset);
	qp->rx_memcpy++;
}