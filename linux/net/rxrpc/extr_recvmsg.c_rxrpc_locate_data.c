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
typedef  unsigned int u8 ;
struct sk_buff {unsigned int len; } ;
struct rxrpc_wire_header {int dummy; } ;
struct rxrpc_skb_priv {int nr_subpackets; int rx_flags; } ;
struct rxrpc_call {TYPE_1__* security; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* locate_data ) (struct rxrpc_call*,struct sk_buff*,unsigned int*,unsigned int*) ;} ;

/* Variables and functions */
 unsigned int RXRPC_JUMBO_DATALEN ; 
 unsigned int RXRPC_JUMBO_SUBPKTLEN ; 
 unsigned int RXRPC_RX_ANNO_SUBPACKET ; 
 unsigned int RXRPC_RX_ANNO_VERIFIED ; 
 int RXRPC_SKB_INCL_LAST ; 
 struct rxrpc_skb_priv* rxrpc_skb (struct sk_buff*) ; 
 int rxrpc_verify_packet (struct rxrpc_call*,struct sk_buff*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct rxrpc_call*,struct sk_buff*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int rxrpc_locate_data(struct rxrpc_call *call, struct sk_buff *skb,
			     u8 *_annotation,
			     unsigned int *_offset, unsigned int *_len,
			     bool *_last)
{
	struct rxrpc_skb_priv *sp = rxrpc_skb(skb);
	unsigned int offset = sizeof(struct rxrpc_wire_header);
	unsigned int len;
	bool last = false;
	int ret;
	u8 annotation = *_annotation;
	u8 subpacket = annotation & RXRPC_RX_ANNO_SUBPACKET;

	/* Locate the subpacket */
	offset += subpacket * RXRPC_JUMBO_SUBPKTLEN;
	len = skb->len - offset;
	if (subpacket < sp->nr_subpackets - 1)
		len = RXRPC_JUMBO_DATALEN;
	else if (sp->rx_flags & RXRPC_SKB_INCL_LAST)
		last = true;

	if (!(annotation & RXRPC_RX_ANNO_VERIFIED)) {
		ret = rxrpc_verify_packet(call, skb, annotation, offset, len);
		if (ret < 0)
			return ret;
		*_annotation |= RXRPC_RX_ANNO_VERIFIED;
	}

	*_offset = offset;
	*_len = len;
	*_last = last;
	call->security->locate_data(call, skb, _offset, _len);
	return 0;
}