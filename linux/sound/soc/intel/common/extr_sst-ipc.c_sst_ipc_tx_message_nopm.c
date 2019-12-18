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
struct sst_ipc_message {int dummy; } ;
struct sst_generic_ipc {int dummy; } ;

/* Variables and functions */
 int ipc_tx_message (struct sst_generic_ipc*,struct sst_ipc_message,struct sst_ipc_message*,int) ; 

int sst_ipc_tx_message_nopm(struct sst_generic_ipc *ipc,
	struct sst_ipc_message request, struct sst_ipc_message *reply)
{
	return ipc_tx_message(ipc, request, reply, 1);
}