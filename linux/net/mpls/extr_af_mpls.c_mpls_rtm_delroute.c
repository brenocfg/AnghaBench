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
struct nlmsghdr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct mpls_route_config {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mpls_route_config*) ; 
 struct mpls_route_config* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mpls_route_del (struct mpls_route_config*,struct netlink_ext_ack*) ; 
 int rtm_to_route_config (struct sk_buff*,struct nlmsghdr*,struct mpls_route_config*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int mpls_rtm_delroute(struct sk_buff *skb, struct nlmsghdr *nlh,
			     struct netlink_ext_ack *extack)
{
	struct mpls_route_config *cfg;
	int err;

	cfg = kzalloc(sizeof(*cfg), GFP_KERNEL);
	if (!cfg)
		return -ENOMEM;

	err = rtm_to_route_config(skb, nlh, cfg, extack);
	if (err < 0)
		goto out;

	err = mpls_route_del(cfg, extack);
out:
	kfree(cfg);

	return err;
}