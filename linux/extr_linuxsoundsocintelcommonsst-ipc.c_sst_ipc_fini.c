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
struct sst_generic_ipc {TYPE_1__* msg; int /*<<< orphan*/  kwork; } ;
struct TYPE_2__ {struct TYPE_2__* rx_data; struct TYPE_2__* tx_data; } ;

/* Variables and functions */
 int IPC_EMPTY_LIST_SIZE ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void sst_ipc_fini(struct sst_generic_ipc *ipc)
{
	int i;

	cancel_work_sync(&ipc->kwork);

	if (ipc->msg) {
		for (i = 0; i < IPC_EMPTY_LIST_SIZE; i++) {
			kfree(ipc->msg[i].tx_data);
			kfree(ipc->msg[i].rx_data);
		}
		kfree(ipc->msg);
	}
}