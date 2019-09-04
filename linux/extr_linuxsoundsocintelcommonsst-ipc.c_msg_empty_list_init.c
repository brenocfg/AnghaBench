#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sst_generic_ipc {TYPE_1__* msg; int /*<<< orphan*/  empty_list; int /*<<< orphan*/  rx_data_max_size; int /*<<< orphan*/  tx_data_max_size; } ;
struct ipc_message {int dummy; } ;
struct TYPE_3__ {struct TYPE_3__* rx_data; struct TYPE_3__* tx_data; int /*<<< orphan*/  list; int /*<<< orphan*/  waitq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IPC_EMPTY_LIST_SIZE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msg_empty_list_init(struct sst_generic_ipc *ipc)
{
	int i;

	ipc->msg = kcalloc(IPC_EMPTY_LIST_SIZE, sizeof(struct ipc_message),
			   GFP_KERNEL);
	if (ipc->msg == NULL)
		return -ENOMEM;

	for (i = 0; i < IPC_EMPTY_LIST_SIZE; i++) {
		ipc->msg[i].tx_data = kzalloc(ipc->tx_data_max_size, GFP_KERNEL);
		if (ipc->msg[i].tx_data == NULL)
			goto free_mem;

		ipc->msg[i].rx_data = kzalloc(ipc->rx_data_max_size, GFP_KERNEL);
		if (ipc->msg[i].rx_data == NULL) {
			kfree(ipc->msg[i].tx_data);
			goto free_mem;
		}

		init_waitqueue_head(&ipc->msg[i].waitq);
		list_add(&ipc->msg[i].list, &ipc->empty_list);
	}

	return 0;

free_mem:
	while (i > 0) {
		kfree(ipc->msg[i-1].tx_data);
		kfree(ipc->msg[i-1].rx_data);
		--i;
	}
	kfree(ipc->msg);

	return -ENOMEM;
}