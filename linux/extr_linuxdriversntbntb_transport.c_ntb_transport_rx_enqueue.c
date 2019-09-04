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
struct ntb_transport_qp {int /*<<< orphan*/  rxc_db_work; scalar_t__ active; int /*<<< orphan*/  rx_pend_q; int /*<<< orphan*/  ntb_rx_q_lock; int /*<<< orphan*/  rx_free_q; } ;
struct ntb_queue_entry {unsigned int len; int /*<<< orphan*/  entry; scalar_t__ rx_index; scalar_t__ errors; scalar_t__ retries; scalar_t__ flags; void* buf; void* cb_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ntb_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ntb_queue_entry* ntb_list_rm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

int ntb_transport_rx_enqueue(struct ntb_transport_qp *qp, void *cb, void *data,
			     unsigned int len)
{
	struct ntb_queue_entry *entry;

	if (!qp)
		return -EINVAL;

	entry = ntb_list_rm(&qp->ntb_rx_q_lock, &qp->rx_free_q);
	if (!entry)
		return -ENOMEM;

	entry->cb_data = cb;
	entry->buf = data;
	entry->len = len;
	entry->flags = 0;
	entry->retries = 0;
	entry->errors = 0;
	entry->rx_index = 0;

	ntb_list_add(&qp->ntb_rx_q_lock, &entry->entry, &qp->rx_pend_q);

	if (qp->active)
		tasklet_schedule(&qp->rxc_db_work);

	return 0;
}