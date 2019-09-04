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
struct fou_cfg {int dummy; } ;

/* Variables and functions */
 int fou_destroy (struct net*,struct fou_cfg*) ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int parse_nl_config (struct genl_info*,struct fou_cfg*) ; 

__attribute__((used)) static int fou_nl_cmd_rm_port(struct sk_buff *skb, struct genl_info *info)
{
	struct net *net = genl_info_net(info);
	struct fou_cfg cfg;
	int err;

	err = parse_nl_config(info, &cfg);
	if (err)
		return err;

	return fou_destroy(net, &cfg);
}