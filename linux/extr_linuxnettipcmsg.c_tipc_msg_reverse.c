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
struct sk_buff {struct tipc_msg* data; } ;

/* Variables and functions */
 int BASIC_H_SIZE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MAX_FORWARD_SIZE ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (struct tipc_msg*,struct tipc_msg*,int) ; 
 int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_msg* msg_data (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_data_sz (struct tipc_msg*) ; 
 scalar_t__ msg_dest_droppable (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_destport (struct tipc_msg*) ; 
 scalar_t__ msg_errcode (struct tipc_msg*) ; 
 int msg_hdr_sz (struct tipc_msg*) ; 
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
 scalar_t__ msg_short (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_size (struct tipc_msg*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* tipc_buf_acquire (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint ; 

bool tipc_msg_reverse(u32 own_node,  struct sk_buff **skb, int err)
{
	struct sk_buff *_skb = *skb;
	struct tipc_msg *hdr;
	struct tipc_msg ohdr;
	int dlen;

	if (skb_linearize(_skb))
		goto exit;
	hdr = buf_msg(_skb);
	dlen = min_t(uint, msg_data_sz(hdr), MAX_FORWARD_SIZE);
	if (msg_dest_droppable(hdr))
		goto exit;
	if (msg_errcode(hdr))
		goto exit;

	/* Take a copy of original header before altering message */
	memcpy(&ohdr, hdr, msg_hdr_sz(hdr));

	/* Never return SHORT header; expand by replacing buffer if necessary */
	if (msg_short(hdr)) {
		*skb = tipc_buf_acquire(BASIC_H_SIZE + dlen, GFP_ATOMIC);
		if (!*skb)
			goto exit;
		memcpy((*skb)->data + BASIC_H_SIZE, msg_data(hdr), dlen);
		kfree_skb(_skb);
		_skb = *skb;
		hdr = buf_msg(_skb);
		memcpy(hdr, &ohdr, BASIC_H_SIZE);
		msg_set_hdr_sz(hdr, BASIC_H_SIZE);
	}

	/* Now reverse the concerned fields */
	msg_set_errcode(hdr, err);
	msg_set_non_seq(hdr, 0);
	msg_set_origport(hdr, msg_destport(&ohdr));
	msg_set_destport(hdr, msg_origport(&ohdr));
	msg_set_destnode(hdr, msg_prevnode(&ohdr));
	msg_set_prevnode(hdr, own_node);
	msg_set_orignode(hdr, own_node);
	msg_set_size(hdr, msg_hdr_sz(hdr) + dlen);
	skb_trim(_skb, msg_size(hdr));
	skb_orphan(_skb);
	return true;
exit:
	kfree_skb(_skb);
	*skb = NULL;
	return false;
}