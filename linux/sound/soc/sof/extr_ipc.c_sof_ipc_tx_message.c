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
typedef  int /*<<< orphan*/  u32 ;
struct snd_sof_ipc {int /*<<< orphan*/  tx_mutex; } ;

/* Variables and functions */
 int ENOBUFS ; 
 size_t SOF_IPC_MSG_MAX_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sof_ipc_tx_message_unlocked (struct snd_sof_ipc*,int /*<<< orphan*/ ,void*,size_t,void*,size_t) ; 

int sof_ipc_tx_message(struct snd_sof_ipc *ipc, u32 header,
		       void *msg_data, size_t msg_bytes, void *reply_data,
		       size_t reply_bytes)
{
	int ret;

	if (msg_bytes > SOF_IPC_MSG_MAX_SIZE ||
	    reply_bytes > SOF_IPC_MSG_MAX_SIZE)
		return -ENOBUFS;

	/* Serialise IPC TX */
	mutex_lock(&ipc->tx_mutex);

	ret = sof_ipc_tx_message_unlocked(ipc, header, msg_data, msg_bytes,
					  reply_data, reply_bytes);

	mutex_unlock(&ipc->tx_mutex);

	return ret;
}