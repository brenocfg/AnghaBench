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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  NF_HOOK_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,int /*<<< orphan*/ *,struct list_head*,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_PRE_ROUTING ; 
 int /*<<< orphan*/  ip_list_rcv_finish (struct net*,int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  ip_rcv_finish ; 

__attribute__((used)) static void ip_sublist_rcv(struct list_head *head, struct net_device *dev,
			   struct net *net)
{
	NF_HOOK_LIST(NFPROTO_IPV4, NF_INET_PRE_ROUTING, net, NULL,
		     head, dev, NULL, ip_rcv_finish);
	ip_list_rcv_finish(net, NULL, head);
}