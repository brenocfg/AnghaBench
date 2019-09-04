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
struct sst_generic_ipc {int /*<<< orphan*/  empty_list; } ;
struct ipc_message {int complete; int /*<<< orphan*/  waitq; int /*<<< orphan*/  list; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void sst_ipc_tx_msg_reply_complete(struct sst_generic_ipc *ipc,
	struct ipc_message *msg)
{
	msg->complete = true;

	if (!msg->wait)
		list_add_tail(&msg->list, &ipc->empty_list);
	else
		wake_up(&msg->waitq);
}