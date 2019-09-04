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
typedef  union vnt_tx_data_head {int dummy; } vnt_tx_data_head ;
struct TYPE_4__ {union vnt_tx_data_head head; } ;
struct TYPE_5__ {TYPE_1__ mic; union vnt_tx_data_head head; } ;
struct vnt_rrv_time_cts {int /*<<< orphan*/  cts_rrv_time_ba; void* rrv_time_b; void* rrv_time_a; } ;
struct TYPE_6__ {TYPE_2__ tx; struct vnt_rrv_time_cts cts; } ;
union vnt_tx_head {TYPE_3__ tx_cts; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnt_usb_send_context {scalar_t__ fb_option; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  need_ack; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  frame_len; struct vnt_private* priv; } ;
struct vnt_private {int /*<<< orphan*/  top_cck_basic_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  PK_TYPE_11B ; 
 int /*<<< orphan*/  vnt_fill_cts_fb_head (struct vnt_usb_send_context*,union vnt_tx_data_head*) ; 
 int /*<<< orphan*/  vnt_fill_cts_head (struct vnt_usb_send_context*,union vnt_tx_data_head*) ; 
 int /*<<< orphan*/  vnt_get_rtscts_rsvtime_le (struct vnt_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* vnt_rxtx_rsvtime_le16 (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 vnt_rxtx_cts(struct vnt_usb_send_context *tx_context,
			union vnt_tx_head *tx_head, bool need_mic)
{
	struct vnt_private *priv = tx_context->priv;
	struct vnt_rrv_time_cts *buf = &tx_head->tx_cts.cts;
	union vnt_tx_data_head *head = &tx_head->tx_cts.tx.head;
	u32 frame_len = tx_context->frame_len;
	u16 current_rate = tx_context->tx_rate;
	u8 need_ack = tx_context->need_ack;

	buf->rrv_time_a = vnt_rxtx_rsvtime_le16(priv, tx_context->pkt_type,
					frame_len, current_rate, need_ack);
	buf->rrv_time_b = vnt_rxtx_rsvtime_le16(priv, PK_TYPE_11B,
				frame_len, priv->top_cck_basic_rate, need_ack);

	buf->cts_rrv_time_ba = vnt_get_rtscts_rsvtime_le(priv, 3,
			tx_context->pkt_type, frame_len, current_rate);

	if (need_mic)
		head = &tx_head->tx_cts.tx.mic.head;

	/* Fill CTS */
	if (tx_context->fb_option)
		return vnt_fill_cts_fb_head(tx_context, head);

	return vnt_fill_cts_head(tx_context, head);
}