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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ INT_H_SIZE ; 
 int /*<<< orphan*/  NAME_DISTRIBUTOR ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,scalar_t__) ; 
 struct sk_buff* tipc_buf_acquire (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_msg_init (scalar_t__,struct tipc_msg*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ tipc_own_addr (struct net*) ; 

__attribute__((used)) static struct sk_buff *named_prepare_buf(struct net *net, u32 type, u32 size,
					 u32 dest)
{
	struct sk_buff *buf = tipc_buf_acquire(INT_H_SIZE + size, GFP_ATOMIC);
	u32 self = tipc_own_addr(net);
	struct tipc_msg *msg;

	if (buf != NULL) {
		msg = buf_msg(buf);
		tipc_msg_init(self, msg, NAME_DISTRIBUTOR,
			      type, INT_H_SIZE, dest);
		msg_set_size(msg, INT_H_SIZE + size);
	}
	return buf;
}