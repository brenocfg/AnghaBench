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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int BASIC_H_SIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAX_FORWARD_SIZE ; 
 int SHORT_H_SIZE ; 
 int TIPC_ERR_OVERLOAD ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ msg_data (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_data_sz (struct tipc_msg*) ; 
 scalar_t__ msg_dest_droppable (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_destport (struct tipc_msg*) ; 
 scalar_t__ msg_errcode (struct tipc_msg*) ; 
 int msg_hdr_sz (struct tipc_msg*) ; 
 scalar_t__ msg_is_syn (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_origport (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_prevnode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_destnode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_errcode (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_hdr_sz (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_non_seq (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_orignode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_origport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_prevnode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,int) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 struct sk_buff* tipc_buf_acquire (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint ; 

bool tipc_msg_reverse(u32 own_node,  struct sk_buff **skb, int err)
{
	struct sk_buff *_skb = *skb;
	struct tipc_msg *_hdr, *hdr;
	int hlen, dlen;

	if (skb_linearize(_skb))
		goto exit;
	_hdr = buf_msg(_skb);
	dlen = min_t(uint, msg_data_sz(_hdr), MAX_FORWARD_SIZE);
	hlen = msg_hdr_sz(_hdr);

	if (msg_dest_droppable(_hdr))
		goto exit;
	if (msg_errcode(_hdr))
		goto exit;

	/* Never return SHORT header */
	if (hlen == SHORT_H_SIZE)
		hlen = BASIC_H_SIZE;

	/* Don't return data along with SYN+, - sender has a clone */
	if (msg_is_syn(_hdr) && err == TIPC_ERR_OVERLOAD)
		dlen = 0;

	/* Allocate new buffer to return */
	*skb = tipc_buf_acquire(hlen + dlen, GFP_ATOMIC);
	if (!*skb)
		goto exit;
	memcpy((*skb)->data, _skb->data, msg_hdr_sz(_hdr));
	memcpy((*skb)->data + hlen, msg_data(_hdr), dlen);

	/* Build reverse header in new buffer */
	hdr = buf_msg(*skb);
	msg_set_hdr_sz(hdr, hlen);
	msg_set_errcode(hdr, err);
	msg_set_non_seq(hdr, 0);
	msg_set_origport(hdr, msg_destport(_hdr));
	msg_set_destport(hdr, msg_origport(_hdr));
	msg_set_destnode(hdr, msg_prevnode(_hdr));
	msg_set_prevnode(hdr, own_node);
	msg_set_orignode(hdr, own_node);
	msg_set_size(hdr, hlen + dlen);
	skb_orphan(_skb);
	kfree_skb(_skb);
	return true;
exit:
	kfree_skb(_skb);
	*skb = NULL;
	return false;
}