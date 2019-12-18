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
struct net {int dummy; } ;
struct genl_info {int dummy; } ;

/* Variables and functions */
 struct net* genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  smc_pnet_remove_by_pnetid (struct net*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smc_pnet_flush(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = genl_info_net(info);

	smc_pnet_remove_by_pnetid(net, NULL);
	return 0;
}