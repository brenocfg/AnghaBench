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
struct vmbus_channel {int dummy; } ;
struct TYPE_2__ {int pkt_type; size_t data_size; } ;
struct hvs_send_buf {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int vmbus_sendpacket (struct vmbus_channel*,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hvs_send_data(struct vmbus_channel *chan,
			 struct hvs_send_buf *send_buf, size_t to_write)
{
	send_buf->hdr.pkt_type = 1;
	send_buf->hdr.data_size = to_write;
	return vmbus_sendpacket(chan, &send_buf->hdr,
				sizeof(send_buf->hdr) + to_write,
				0, VM_PKT_DATA_INBAND, 0);
}