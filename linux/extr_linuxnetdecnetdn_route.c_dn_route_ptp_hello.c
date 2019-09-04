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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  dn_dev_hello (struct sk_buff*) ; 
 int /*<<< orphan*/  dn_neigh_pointopoint_hello (struct sk_buff*) ; 

__attribute__((used)) static int dn_route_ptp_hello(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	dn_dev_hello(skb);
	dn_neigh_pointopoint_hello(skb);
	return NET_RX_SUCCESS;
}