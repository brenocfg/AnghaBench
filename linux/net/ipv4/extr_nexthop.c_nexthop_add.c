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
struct nh_config {int nlflags; int /*<<< orphan*/  nh_protocol; scalar_t__ nh_id; scalar_t__ nh_grp; } ;
struct nexthop {struct net* net; int /*<<< orphan*/  protocol; scalar_t__ id; int /*<<< orphan*/  refcnt; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nexthop* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct nexthop*) ; 
 int NLM_F_REPLACE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  __remove_nexthop (struct net*,struct nexthop*,int /*<<< orphan*/ *) ; 
 int insert_nexthop (struct net*,struct nexthop*,struct nh_config*,struct netlink_ext_ack*) ; 
 struct nexthop* nexthop_create (struct net*,struct nh_config*,struct netlink_ext_ack*) ; 
 struct nexthop* nexthop_create_group (struct net*,struct nh_config*) ; 
 int /*<<< orphan*/  nexthop_put (struct nexthop*) ; 
 scalar_t__ nh_find_unused_id (struct net*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct nexthop *nexthop_add(struct net *net, struct nh_config *cfg,
				   struct netlink_ext_ack *extack)
{
	struct nexthop *nh;
	int err;

	if (cfg->nlflags & NLM_F_REPLACE && !cfg->nh_id) {
		NL_SET_ERR_MSG(extack, "Replace requires nexthop id");
		return ERR_PTR(-EINVAL);
	}

	if (!cfg->nh_id) {
		cfg->nh_id = nh_find_unused_id(net);
		if (!cfg->nh_id) {
			NL_SET_ERR_MSG(extack, "No unused id");
			return ERR_PTR(-EINVAL);
		}
	}

	if (cfg->nh_grp)
		nh = nexthop_create_group(net, cfg);
	else
		nh = nexthop_create(net, cfg, extack);

	if (IS_ERR(nh))
		return nh;

	refcount_set(&nh->refcnt, 1);
	nh->id = cfg->nh_id;
	nh->protocol = cfg->nh_protocol;
	nh->net = net;

	err = insert_nexthop(net, nh, cfg, extack);
	if (err) {
		__remove_nexthop(net, nh, NULL);
		nexthop_put(nh);
		nh = ERR_PTR(err);
	}

	return nh;
}