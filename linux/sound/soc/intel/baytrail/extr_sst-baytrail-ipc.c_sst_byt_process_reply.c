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
typedef  int u64 ;
struct sst_byt {int /*<<< orphan*/  ipc; int /*<<< orphan*/  dsp; } ;
struct TYPE_2__ {int header; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct ipc_message {int /*<<< orphan*/  list; TYPE_1__ rx; } ;

/* Variables and functions */
 int IPC_HEADER_LARGE (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sst_byt_header_data (int) ; 
 int /*<<< orphan*/  sst_byt_stream_update (struct sst_byt*,struct ipc_message*) ; 
 int /*<<< orphan*/  sst_dsp_inbox_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipc_message* sst_ipc_reply_find_msg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sst_ipc_tx_msg_reply_complete (int /*<<< orphan*/ *,struct ipc_message*) ; 

__attribute__((used)) static int sst_byt_process_reply(struct sst_byt *byt, u64 header)
{
	struct ipc_message *msg;

	msg = sst_ipc_reply_find_msg(&byt->ipc, header);
	if (msg == NULL)
		return 1;

	msg->rx.header = header;
	if (header & IPC_HEADER_LARGE(true)) {
		msg->rx.size = sst_byt_header_data(header);
		sst_dsp_inbox_read(byt->dsp, msg->rx.data, msg->rx.size);
	}

	/* update any stream states */
	sst_byt_stream_update(byt, msg);

	list_del(&msg->list);
	/* wake up */
	sst_ipc_tx_msg_reply_complete(&byt->ipc, msg);

	return 1;
}