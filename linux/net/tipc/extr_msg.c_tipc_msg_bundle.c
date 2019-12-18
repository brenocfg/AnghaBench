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
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ BCAST_PROTOCOL ; 
 scalar_t__ INT_H_SIZE ; 
 scalar_t__ MSG_BUNDLER ; 
 scalar_t__ MSG_FRAGMENTER ; 
 scalar_t__ TIPC_SYSTEM_IMPORTANCE ; 
 scalar_t__ TUNNEL_PROTOCOL ; 
 scalar_t__ align (unsigned int) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ msg_importance (struct tipc_msg*) ; 
 scalar_t__ msg_msgcnt (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_set_msgcnt (struct tipc_msg*,scalar_t__) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,scalar_t__) ; 
 unsigned int msg_size (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,scalar_t__,struct tipc_msg*,unsigned int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

bool tipc_msg_bundle(struct sk_buff *skb, struct tipc_msg *msg, u32 mtu)
{
	struct tipc_msg *bmsg;
	unsigned int bsz;
	unsigned int msz = msg_size(msg);
	u32 start, pad;
	u32 max = mtu - INT_H_SIZE;

	if (likely(msg_user(msg) == MSG_FRAGMENTER))
		return false;
	if (!skb)
		return false;
	bmsg = buf_msg(skb);
	bsz = msg_size(bmsg);
	start = align(bsz);
	pad = start - bsz;

	if (unlikely(msg_user(msg) == TUNNEL_PROTOCOL))
		return false;
	if (unlikely(msg_user(msg) == BCAST_PROTOCOL))
		return false;
	if (unlikely(msg_user(bmsg) != MSG_BUNDLER))
		return false;
	if (unlikely(skb_tailroom(skb) < (pad + msz)))
		return false;
	if (unlikely(max < (start + msz)))
		return false;
	if ((msg_importance(msg) < TIPC_SYSTEM_IMPORTANCE) &&
	    (msg_importance(bmsg) == TIPC_SYSTEM_IMPORTANCE))
		return false;

	skb_put(skb, pad + msz);
	skb_copy_to_linear_data_offset(skb, start, msg, msz);
	msg_set_size(bmsg, start + msz);
	msg_set_msgcnt(bmsg, msg_msgcnt(bmsg) + 1);
	return true;
}