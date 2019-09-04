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
struct ntb_transport_qp {int /*<<< orphan*/  tx_free_q; int /*<<< orphan*/  ntb_tx_free_q_lock; int /*<<< orphan*/  tx_err_no_buf; int /*<<< orphan*/  link_is_up; } ;
struct ntb_queue_entry {unsigned int len; int /*<<< orphan*/  entry; scalar_t__ tx_index; scalar_t__ retries; scalar_t__ errors; scalar_t__ flags; void* buf; void* cb_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ntb_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ntb_queue_entry* ntb_list_rm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntb_process_tx (struct ntb_transport_qp*,struct ntb_queue_entry*) ; 

int ntb_transport_tx_enqueue(struct ntb_transport_qp *qp, void *cb, void *data,
			     unsigned int len)
{
	struct ntb_queue_entry *entry;
	int rc;

	if (!qp || !qp->link_is_up || !len)
		return -EINVAL;

	entry = ntb_list_rm(&qp->ntb_tx_free_q_lock, &qp->tx_free_q);
	if (!entry) {
		qp->tx_err_no_buf++;
		return -EBUSY;
	}

	entry->cb_data = cb;
	entry->buf = data;
	entry->len = len;
	entry->flags = 0;
	entry->errors = 0;
	entry->retries = 0;
	entry->tx_index = 0;

	rc = ntb_process_tx(qp, entry);
	if (rc)
		ntb_list_add(&qp->ntb_tx_free_q_lock, &entry->entry,
			     &qp->tx_free_q);

	return rc;
}