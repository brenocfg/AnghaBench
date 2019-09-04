#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct htc_target {int /*<<< orphan*/  free_ctrl_txbuf; int /*<<< orphan*/  free_ctrl_rxbuf; TYPE_3__* dev; } ;
struct htc_packet {int /*<<< orphan*/  list; int /*<<< orphan*/  endpoint; void* buf_start; void* buf; scalar_t__ act_len; scalar_t__ buf_len; } ;
struct TYPE_6__ {TYPE_2__* ar; } ;
struct TYPE_4__ {scalar_t__ block_size; } ;
struct TYPE_5__ {TYPE_1__ mbox_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDPOINT_0 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HTC_HDR_LENGTH ; 
 scalar_t__ HTC_MAX_CTRL_MSG_LEN ; 
 int NUM_CONTROL_BUFFERS ; 
 int NUM_CONTROL_RX_BUFFERS ; 
 int /*<<< orphan*/  kfree (struct htc_packet*) ; 
 void* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_ep_state (struct htc_target*) ; 

__attribute__((used)) static int ath6kl_htc_reset(struct htc_target *target)
{
	u32 block_size, ctrl_bufsz;
	struct htc_packet *packet;
	int i;

	reset_ep_state(target);

	block_size = target->dev->ar->mbox_info.block_size;

	ctrl_bufsz = (block_size > HTC_MAX_CTRL_MSG_LEN) ?
		      (block_size + HTC_HDR_LENGTH) :
		      (HTC_MAX_CTRL_MSG_LEN + HTC_HDR_LENGTH);

	for (i = 0; i < NUM_CONTROL_BUFFERS; i++) {
		packet = kzalloc(sizeof(*packet), GFP_KERNEL);
		if (!packet)
			return -ENOMEM;

		packet->buf_start = kzalloc(ctrl_bufsz, GFP_KERNEL);
		if (!packet->buf_start) {
			kfree(packet);
			return -ENOMEM;
		}

		packet->buf_len = ctrl_bufsz;
		if (i < NUM_CONTROL_RX_BUFFERS) {
			packet->act_len = 0;
			packet->buf = packet->buf_start;
			packet->endpoint = ENDPOINT_0;
			list_add_tail(&packet->list, &target->free_ctrl_rxbuf);
		} else {
			list_add_tail(&packet->list, &target->free_ctrl_txbuf);
		}
	}

	return 0;
}