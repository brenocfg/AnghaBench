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
struct tipc_msg {int dummy; } ;
struct tipc_link {int /*<<< orphan*/  name; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  link_print (struct tipc_link*,char*) ; 
 int /*<<< orphan*/  msg_errcode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_orignode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_prevnode (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_seqno (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_size (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_type (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void link_retransmit_failure(struct tipc_link *l, struct sk_buff *skb)
{
	struct tipc_msg *hdr = buf_msg(skb);

	pr_warn("Retransmission failure on link <%s>\n", l->name);
	link_print(l, "State of link ");
	pr_info("Failed msg: usr %u, typ %u, len %u, err %u\n",
		msg_user(hdr), msg_type(hdr), msg_size(hdr), msg_errcode(hdr));
	pr_info("sqno %u, prev: %x, src: %x\n",
		msg_seqno(hdr), msg_prevnode(hdr), msg_orignode(hdr));
}