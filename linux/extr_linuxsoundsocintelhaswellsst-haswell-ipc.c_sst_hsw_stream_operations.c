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
typedef  int u32 ;
struct sst_hsw {int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_GLB_STREAM_MESSAGE ; 
 int IPC_GLB_TYPE (int /*<<< orphan*/ ) ; 
 int IPC_STR_ID_SHIFT ; 
 int IPC_STR_TYPE (int) ; 
 int sst_ipc_tx_message_nowait (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_hsw_stream_operations(struct sst_hsw *hsw, int type,
	int stream_id, int wait)
{
	u32 header;

	header = IPC_GLB_TYPE(IPC_GLB_STREAM_MESSAGE) | IPC_STR_TYPE(type);
	header |= (stream_id << IPC_STR_ID_SHIFT);

	if (wait)
		return sst_ipc_tx_message_wait(&hsw->ipc, header,
			NULL, 0, NULL, 0);
	else
		return sst_ipc_tx_message_nowait(&hsw->ipc, header, NULL, 0);
}