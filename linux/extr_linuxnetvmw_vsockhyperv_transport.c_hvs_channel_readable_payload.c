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
typedef  scalar_t__ u32 ;
struct vmbus_channel {int /*<<< orphan*/  inbound; } ;

/* Variables and functions */
 scalar_t__ HVS_PKT_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ hv_get_bytes_to_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hvs_channel_readable_payload(struct vmbus_channel *chan)
{
	u32 readable = hv_get_bytes_to_read(&chan->inbound);

	if (readable > HVS_PKT_LEN(0)) {
		/* At least we have 1 byte to read. We don't need to return
		 * the exact readable bytes: see vsock_stream_recvmsg() ->
		 * vsock_stream_has_data().
		 */
		return 1;
	}

	if (readable == HVS_PKT_LEN(0)) {
		/* 0-size payload means FIN */
		return 0;
	}

	/* No payload or FIN */
	return -1;
}