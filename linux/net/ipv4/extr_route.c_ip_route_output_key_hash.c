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
struct sk_buff {int dummy; } ;
struct rtable {int dummy; } ;
struct net {int dummy; } ;
struct flowi4 {int flowi4_tos; int /*<<< orphan*/  flowi4_scope; int /*<<< orphan*/  flowi4_iif; } ;
struct fib_result {int /*<<< orphan*/  tclassid; int /*<<< orphan*/ * table; int /*<<< orphan*/ * fi; int /*<<< orphan*/  type; } ;
typedef  int __u8 ;

/* Variables and functions */
 int IPTOS_RT_MASK ; 
 int /*<<< orphan*/  LOOPBACK_IFINDEX ; 
 int /*<<< orphan*/  RTN_UNSPEC ; 
 int RTO_ONLINK ; 
 int RT_FL_TOS (struct flowi4*) ; 
 int /*<<< orphan*/  RT_SCOPE_LINK ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 struct rtable* ip_route_output_key_hash_rcu (struct net*,struct flowi4*,struct fib_result*,struct sk_buff const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct rtable *ip_route_output_key_hash(struct net *net, struct flowi4 *fl4,
					const struct sk_buff *skb)
{
	__u8 tos = RT_FL_TOS(fl4);
	struct fib_result res = {
		.type		= RTN_UNSPEC,
		.fi		= NULL,
		.table		= NULL,
		.tclassid	= 0,
	};
	struct rtable *rth;

	fl4->flowi4_iif = LOOPBACK_IFINDEX;
	fl4->flowi4_tos = tos & IPTOS_RT_MASK;
	fl4->flowi4_scope = ((tos & RTO_ONLINK) ?
			 RT_SCOPE_LINK : RT_SCOPE_UNIVERSE);

	rcu_read_lock();
	rth = ip_route_output_key_hash_rcu(net, fl4, &res, skb);
	rcu_read_unlock();

	return rth;
}