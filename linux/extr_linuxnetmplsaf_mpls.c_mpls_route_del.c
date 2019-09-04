#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct net* nl_net; } ;
struct mpls_route_config {unsigned int rc_label; TYPE_1__ rc_nlinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mpls_label_ok (struct net*,unsigned int*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  mpls_route_update (struct net*,unsigned int,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int mpls_route_del(struct mpls_route_config *cfg,
			  struct netlink_ext_ack *extack)
{
	struct net *net = cfg->rc_nlinfo.nl_net;
	unsigned index;
	int err = -EINVAL;

	index = cfg->rc_label;

	if (!mpls_label_ok(net, &index, extack))
		goto errout;

	mpls_route_update(net, index, NULL, &cfg->rc_nlinfo);

	err = 0;
errout:
	return err;
}