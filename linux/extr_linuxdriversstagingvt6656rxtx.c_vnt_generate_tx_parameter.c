#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vnt_usb_send_context {scalar_t__ pkt_type; } ;
struct vnt_mic_hdr {int dummy; } ;
struct TYPE_20__ {struct vnt_mic_hdr hdr; } ;
struct TYPE_21__ {TYPE_7__ mic; } ;
struct TYPE_22__ {TYPE_8__ tx; } ;
struct TYPE_17__ {struct vnt_mic_hdr hdr; } ;
struct TYPE_18__ {TYPE_4__ mic; } ;
struct TYPE_19__ {TYPE_5__ tx; } ;
struct TYPE_14__ {struct vnt_mic_hdr hdr; } ;
struct TYPE_15__ {TYPE_1__ mic; } ;
struct TYPE_16__ {TYPE_2__ tx; } ;
struct TYPE_13__ {TYPE_9__ tx_ab; TYPE_6__ tx_cts; TYPE_3__ tx_rts; } ;
struct vnt_tx_buffer {TYPE_10__ tx_head; } ;

/* Variables and functions */
 scalar_t__ PK_TYPE_11GA ; 
 scalar_t__ PK_TYPE_11GB ; 
 int /*<<< orphan*/  vnt_rxtx_ab (struct vnt_usb_send_context*,TYPE_10__*,int,scalar_t__) ; 
 int /*<<< orphan*/  vnt_rxtx_cts (struct vnt_usb_send_context*,TYPE_10__*,scalar_t__) ; 
 int /*<<< orphan*/  vnt_rxtx_rts (struct vnt_usb_send_context*,TYPE_10__*,scalar_t__) ; 

__attribute__((used)) static u16 vnt_generate_tx_parameter(struct vnt_usb_send_context *tx_context,
				     struct vnt_tx_buffer *tx_buffer,
				     struct vnt_mic_hdr **mic_hdr, u32 need_mic,
				     bool need_rts)
{
	if (tx_context->pkt_type == PK_TYPE_11GB ||
	    tx_context->pkt_type == PK_TYPE_11GA) {
		if (need_rts) {
			if (need_mic)
				*mic_hdr =
					&tx_buffer->tx_head.tx_rts.tx.mic.hdr;

			return vnt_rxtx_rts(tx_context, &tx_buffer->tx_head,
					    need_mic);
		}

		if (need_mic)
			*mic_hdr = &tx_buffer->tx_head.tx_cts.tx.mic.hdr;

		return vnt_rxtx_cts(tx_context, &tx_buffer->tx_head, need_mic);
	}

	if (need_mic)
		*mic_hdr = &tx_buffer->tx_head.tx_ab.tx.mic.hdr;

	return vnt_rxtx_ab(tx_context, &tx_buffer->tx_head, need_rts, need_mic);
}