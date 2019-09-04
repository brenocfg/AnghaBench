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
struct sock {int sk_protocol; } ;
struct sk_buff {struct sock* sk; } ;

/* Variables and functions */
#define  NETLINK_FIB_LOOKUP 135 
#define  NETLINK_GENERIC 134 
#define  NETLINK_NETFILTER 133 
#define  NETLINK_NFLOG 132 
#define  NETLINK_ROUTE 131 
#define  NETLINK_SOCK_DIAG 130 
#define  NETLINK_USERSOCK 129 
#define  NETLINK_XFRM 128 

__attribute__((used)) static bool netlink_filter_tap(const struct sk_buff *skb)
{
	struct sock *sk = skb->sk;

	/* We take the more conservative approach and
	 * whitelist socket protocols that may pass.
	 */
	switch (sk->sk_protocol) {
	case NETLINK_ROUTE:
	case NETLINK_USERSOCK:
	case NETLINK_SOCK_DIAG:
	case NETLINK_NFLOG:
	case NETLINK_XFRM:
	case NETLINK_FIB_LOOKUP:
	case NETLINK_NETFILTER:
	case NETLINK_GENERIC:
		return true;
	}

	return false;
}