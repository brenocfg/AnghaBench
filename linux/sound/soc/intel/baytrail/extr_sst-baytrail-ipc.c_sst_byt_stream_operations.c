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
struct sst_ipc_message {int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct sst_byt {int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  sst_byt_header (int,int /*<<< orphan*/ ,int,int) ; 
 int sst_ipc_tx_message_nowait (int /*<<< orphan*/ *,struct sst_ipc_message) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,struct sst_ipc_message,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sst_byt_stream_operations(struct sst_byt *byt, int type,
				     int stream_id, int wait)
{
	struct sst_ipc_message request = {0};

	request.header = sst_byt_header(type, 0, false, stream_id);
	if (wait)
		return sst_ipc_tx_message_wait(&byt->ipc, request, NULL);
	else
		return sst_ipc_tx_message_nowait(&byt->ipc, request);
}