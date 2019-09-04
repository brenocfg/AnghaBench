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
typedef  int /*<<< orphan*/  u64 ;
struct sst_byt {int /*<<< orphan*/  ipc; } ;

/* Variables and functions */
 int /*<<< orphan*/  sst_byt_header (int,int /*<<< orphan*/ ,int,int) ; 
 int sst_ipc_tx_message_nowait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sst_ipc_tx_message_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_byt_stream_operations(struct sst_byt *byt, int type,
				     int stream_id, int wait)
{
	u64 header;

	header = sst_byt_header(type, 0, false, stream_id);
	if (wait)
		return sst_ipc_tx_message_wait(&byt->ipc, header, NULL,
						0, NULL, 0);
	else
		return sst_ipc_tx_message_nowait(&byt->ipc, header,
						NULL, 0);
}