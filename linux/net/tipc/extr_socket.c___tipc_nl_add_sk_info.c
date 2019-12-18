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
struct sock {int dummy; } ;
struct tipc_sock {int /*<<< orphan*/  publications; int /*<<< orphan*/  portid; struct sock sk; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK_ADDR ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK_HAS_PUBL ; 
 int /*<<< orphan*/  TIPC_NLA_SOCK_REF ; 
 scalar_t__ __tipc_nl_add_sk_con (struct sk_buff*,struct tipc_sock*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 
 scalar_t__ tipc_sk_connected (struct sock*) ; 

__attribute__((used)) static int __tipc_nl_add_sk_info(struct sk_buff *skb, struct tipc_sock
			  *tsk)
{
	struct net *net = sock_net(skb->sk);
	struct sock *sk = &tsk->sk;

	if (nla_put_u32(skb, TIPC_NLA_SOCK_REF, tsk->portid) ||
	    nla_put_u32(skb, TIPC_NLA_SOCK_ADDR, tipc_own_addr(net)))
		return -EMSGSIZE;

	if (tipc_sk_connected(sk)) {
		if (__tipc_nl_add_sk_con(skb, tsk))
			return -EMSGSIZE;
	} else if (!list_empty(&tsk->publications)) {
		if (nla_put_flag(skb, TIPC_NLA_SOCK_HAS_PUBL))
			return -EMSGSIZE;
	}
	return 0;
}