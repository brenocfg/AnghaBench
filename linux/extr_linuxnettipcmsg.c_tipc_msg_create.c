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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ SHORT_H_SIZE ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_set_destnode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_destport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_errcode (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_orignode (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_origport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,scalar_t__) ; 
 struct sk_buff* tipc_buf_acquire (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_msg_init (int /*<<< orphan*/ ,struct tipc_msg*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *tipc_msg_create(uint user, uint type,
				uint hdr_sz, uint data_sz, u32 dnode,
				u32 onode, u32 dport, u32 oport, int errcode)
{
	struct tipc_msg *msg;
	struct sk_buff *buf;

	buf = tipc_buf_acquire(hdr_sz + data_sz, GFP_ATOMIC);
	if (unlikely(!buf))
		return NULL;

	msg = buf_msg(buf);
	tipc_msg_init(onode, msg, user, type, hdr_sz, dnode);
	msg_set_size(msg, hdr_sz + data_sz);
	msg_set_origport(msg, oport);
	msg_set_destport(msg, dport);
	msg_set_errcode(msg, errcode);
	if (hdr_sz > SHORT_H_SIZE) {
		msg_set_orignode(msg, onode);
		msg_set_destnode(msg, dnode);
	}
	return buf;
}