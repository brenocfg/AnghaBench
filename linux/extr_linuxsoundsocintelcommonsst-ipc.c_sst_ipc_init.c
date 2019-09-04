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
struct sst_generic_ipc {int /*<<< orphan*/  kwork; int /*<<< orphan*/  wait_txq; int /*<<< orphan*/  empty_list; int /*<<< orphan*/  rx_list; int /*<<< orphan*/  tx_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_tx_msgs ; 
 int msg_empty_list_init (struct sst_generic_ipc*) ; 

int sst_ipc_init(struct sst_generic_ipc *ipc)
{
	int ret;

	INIT_LIST_HEAD(&ipc->tx_list);
	INIT_LIST_HEAD(&ipc->rx_list);
	INIT_LIST_HEAD(&ipc->empty_list);
	init_waitqueue_head(&ipc->wait_txq);

	ret = msg_empty_list_init(ipc);
	if (ret < 0)
		return -ENOMEM;

	INIT_WORK(&ipc->kwork, ipc_tx_msgs);
	return 0;
}