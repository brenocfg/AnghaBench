#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct hvsock {scalar_t__ recv_data_off; scalar_t__ recv_data_len; TYPE_2__* vsk; scalar_t__ recv_desc; } ;
struct TYPE_3__ {scalar_t__ data_size; } ;
struct hvs_recv_buf {TYPE_1__ hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  peer_shutdown; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ HVS_MTU_SIZE ; 
 int /*<<< orphan*/  SEND_SHUTDOWN ; 

__attribute__((used)) static int hvs_update_recv_data(struct hvsock *hvs)
{
	struct hvs_recv_buf *recv_buf;
	u32 payload_len;

	recv_buf = (struct hvs_recv_buf *)(hvs->recv_desc + 1);
	payload_len = recv_buf->hdr.data_size;

	if (payload_len > HVS_MTU_SIZE)
		return -EIO;

	if (payload_len == 0)
		hvs->vsk->peer_shutdown |= SEND_SHUTDOWN;

	hvs->recv_data_len = payload_len;
	hvs->recv_data_off = 0;

	return 0;
}