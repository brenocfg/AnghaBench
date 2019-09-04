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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  (* tx_data_copy ) (struct ipc_message*,void*,size_t) ;} ;
struct sst_generic_ipc {TYPE_2__* dsp; int /*<<< orphan*/  kwork; int /*<<< orphan*/  tx_list; TYPE_1__ ops; } ;
struct ipc_message {size_t tx_size; size_t rx_size; int wait; int pending; int complete; int /*<<< orphan*/  list; scalar_t__ errno; int /*<<< orphan*/  header; } ;
struct TYPE_4__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipc_message* msg_get_empty (struct sst_generic_ipc*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ipc_message*,void*,size_t) ; 
 int tx_wait_done (struct sst_generic_ipc*,struct ipc_message*,void*) ; 

__attribute__((used)) static int ipc_tx_message(struct sst_generic_ipc *ipc, u64 header,
	void *tx_data, size_t tx_bytes, void *rx_data,
	size_t rx_bytes, int wait)
{
	struct ipc_message *msg;
	unsigned long flags;

	spin_lock_irqsave(&ipc->dsp->spinlock, flags);

	msg = msg_get_empty(ipc);
	if (msg == NULL) {
		spin_unlock_irqrestore(&ipc->dsp->spinlock, flags);
		return -EBUSY;
	}

	msg->header = header;
	msg->tx_size = tx_bytes;
	msg->rx_size = rx_bytes;
	msg->wait = wait;
	msg->errno = 0;
	msg->pending = false;
	msg->complete = false;

	if ((tx_bytes) && (ipc->ops.tx_data_copy != NULL))
		ipc->ops.tx_data_copy(msg, tx_data, tx_bytes);

	list_add_tail(&msg->list, &ipc->tx_list);
	schedule_work(&ipc->kwork);
	spin_unlock_irqrestore(&ipc->dsp->spinlock, flags);

	if (wait)
		return tx_wait_done(ipc, msg, rx_data);
	else
		return 0;
}