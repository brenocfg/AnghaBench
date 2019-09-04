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
struct ntb_transport_qp {int tx_max_frame; int /*<<< orphan*/  tx_pkts; int /*<<< orphan*/  tx_max_entry; int /*<<< orphan*/  tx_index; int /*<<< orphan*/  tx_free_q; int /*<<< orphan*/  ntb_tx_free_q_lock; int /*<<< orphan*/  cb_data; int /*<<< orphan*/  (* tx_handler ) (struct ntb_transport_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tx_ring_full; TYPE_1__* remote_rx_info; } ;
struct ntb_queue_entry {int len; int /*<<< orphan*/  entry; } ;
struct ntb_payload_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ntb_async_tx (struct ntb_transport_qp*,struct ntb_queue_entry*) ; 
 int /*<<< orphan*/  ntb_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ntb_transport_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ntb_process_tx(struct ntb_transport_qp *qp,
			  struct ntb_queue_entry *entry)
{
	if (qp->tx_index == qp->remote_rx_info->entry) {
		qp->tx_ring_full++;
		return -EAGAIN;
	}

	if (entry->len > qp->tx_max_frame - sizeof(struct ntb_payload_header)) {
		if (qp->tx_handler)
			qp->tx_handler(qp, qp->cb_data, NULL, -EIO);

		ntb_list_add(&qp->ntb_tx_free_q_lock, &entry->entry,
			     &qp->tx_free_q);
		return 0;
	}

	ntb_async_tx(qp, entry);

	qp->tx_index++;
	qp->tx_index %= qp->tx_max_entry;

	qp->tx_pkts++;

	return 0;
}