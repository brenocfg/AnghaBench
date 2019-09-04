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
typedef  int u8 ;
struct sk_buff {unsigned int len; } ;
struct rxrpc_wire_header {int dummy; } ;
struct rxrpc_call {TYPE_2__* conn; } ;
struct TYPE_4__ {TYPE_1__* security; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* locate_data ) (struct rxrpc_call*,struct sk_buff*,unsigned int*,unsigned int*) ;} ;

/* Variables and functions */
 int RXRPC_JUMBO_SUBPKTLEN ; 
 int RXRPC_RX_ANNO_JLAST ; 
 int RXRPC_RX_ANNO_JUMBO ; 
 int RXRPC_RX_ANNO_VERIFIED ; 
 int rxrpc_verify_packet (struct rxrpc_call*,struct sk_buff*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct rxrpc_call*,struct sk_buff*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int rxrpc_locate_data(struct rxrpc_call *call, struct sk_buff *skb,
			     u8 *_annotation,
			     unsigned int *_offset, unsigned int *_len)
{
	unsigned int offset = sizeof(struct rxrpc_wire_header);
	unsigned int len;
	int ret;
	u8 annotation = *_annotation;

	/* Locate the subpacket */
	len = skb->len - offset;
	if ((annotation & RXRPC_RX_ANNO_JUMBO) > 0) {
		offset += (((annotation & RXRPC_RX_ANNO_JUMBO) - 1) *
			   RXRPC_JUMBO_SUBPKTLEN);
		len = (annotation & RXRPC_RX_ANNO_JLAST) ?
			skb->len - offset : RXRPC_JUMBO_SUBPKTLEN;
	}

	if (!(annotation & RXRPC_RX_ANNO_VERIFIED)) {
		ret = rxrpc_verify_packet(call, skb, annotation, offset, len);
		if (ret < 0)
			return ret;
		*_annotation |= RXRPC_RX_ANNO_VERIFIED;
	}

	*_offset = offset;
	*_len = len;
	call->conn->security->locate_data(call, skb, _offset, _len);
	return 0;
}