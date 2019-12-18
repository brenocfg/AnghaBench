#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sst_ipc_message {scalar_t__ size; int /*<<< orphan*/  data; int /*<<< orphan*/  header; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* tx_data_copy ) (struct ipc_message*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct sst_generic_ipc {TYPE_4__* dsp; int /*<<< orphan*/  kwork; int /*<<< orphan*/  tx_list; TYPE_3__ ops; } ;
struct TYPE_6__ {scalar_t__ size; scalar_t__ header; } ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  header; } ;
struct ipc_message {int wait; int pending; int complete; int /*<<< orphan*/  list; scalar_t__ errno; TYPE_2__ rx; TYPE_1__ tx; } ;
struct TYPE_8__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipc_message* msg_get_empty (struct sst_generic_ipc*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ipc_message*,int /*<<< orphan*/ ,scalar_t__) ; 
 int tx_wait_done (struct sst_generic_ipc*,struct ipc_message*,struct sst_ipc_message*) ; 

__attribute__((used)) static int ipc_tx_message(struct sst_generic_ipc *ipc,
	struct sst_ipc_message request,
	struct sst_ipc_message *reply, int wait)
{
	struct ipc_message *msg;
	unsigned long flags;

	spin_lock_irqsave(&ipc->dsp->spinlock, flags);

	msg = msg_get_empty(ipc);
	if (msg == NULL) {
		spin_unlock_irqrestore(&ipc->dsp->spinlock, flags);
		return -EBUSY;
	}

	msg->tx.header = request.header;
	msg->tx.size = request.size;
	msg->rx.header = 0;
	msg->rx.size = reply ? reply->size : 0;
	msg->wait = wait;
	msg->errno = 0;
	msg->pending = false;
	msg->complete = false;

	if ((request.size) && (ipc->ops.tx_data_copy != NULL))
		ipc->ops.tx_data_copy(msg, request.data, request.size);

	list_add_tail(&msg->list, &ipc->tx_list);
	schedule_work(&ipc->kwork);
	spin_unlock_irqrestore(&ipc->dsp->spinlock, flags);

	if (wait)
		return tx_wait_done(ipc, msg, reply);
	else
		return 0;
}