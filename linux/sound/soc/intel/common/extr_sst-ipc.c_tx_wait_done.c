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
struct sst_ipc_message {scalar_t__ data; int /*<<< orphan*/  header; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* shim_dbg ) (struct sst_generic_ipc*,char*) ;} ;
struct sst_generic_ipc {TYPE_3__* dsp; int /*<<< orphan*/  empty_list; TYPE_1__ ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; int /*<<< orphan*/  header; } ;
struct ipc_message {int errno; int /*<<< orphan*/  list; TYPE_2__ rx; int /*<<< orphan*/  complete; int /*<<< orphan*/  waitq; } ;
struct TYPE_6__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IPC_TIMEOUT_MSECS ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sst_generic_ipc*,char*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tx_wait_done(struct sst_generic_ipc *ipc,
	struct ipc_message *msg, struct sst_ipc_message *reply)
{
	unsigned long flags;
	int ret;

	/* wait for DSP completion (in all cases atm inc pending) */
	ret = wait_event_timeout(msg->waitq, msg->complete,
		msecs_to_jiffies(IPC_TIMEOUT_MSECS));

	spin_lock_irqsave(&ipc->dsp->spinlock, flags);
	if (ret == 0) {
		if (ipc->ops.shim_dbg != NULL)
			ipc->ops.shim_dbg(ipc, "message timeout");

		list_del(&msg->list);
		ret = -ETIMEDOUT;
	} else {

		/* copy the data returned from DSP */
		if (reply) {
			reply->header = msg->rx.header;
			if (reply->data)
				memcpy(reply->data, msg->rx.data, msg->rx.size);
		}
		ret = msg->errno;
	}

	list_add_tail(&msg->list, &ipc->empty_list);
	spin_unlock_irqrestore(&ipc->dsp->spinlock, flags);
	return ret;
}