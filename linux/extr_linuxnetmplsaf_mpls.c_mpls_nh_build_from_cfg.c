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
struct net {int dummy; } ;
struct TYPE_2__ {struct net* nl_net; } ;
struct mpls_route_config {int rc_output_labels; int /*<<< orphan*/  rc_ifindex; int /*<<< orphan*/  rc_via_alen; int /*<<< orphan*/  rc_via; int /*<<< orphan*/  rc_via_table; int /*<<< orphan*/ * rc_output_label; TYPE_1__ rc_nlinfo; } ;
struct mpls_route {int /*<<< orphan*/  rt_nhn_alive; struct mpls_nh* rt_nh; } ;
struct mpls_nh {int nh_labels; int nh_flags; int /*<<< orphan*/  nh_via_alen; int /*<<< orphan*/  nh_via_table; int /*<<< orphan*/ * nh_label; } ;

/* Variables and functions */
 int ENOMEM ; 
 int RTNH_F_DEAD ; 
 int RTNH_F_LINKDOWN ; 
 int /*<<< orphan*/  __mpls_nh_via (struct mpls_route*,struct mpls_nh*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mpls_nh_assign_dev (struct net*,struct mpls_route*,struct mpls_nh*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpls_nh_build_from_cfg(struct mpls_route_config *cfg,
				  struct mpls_route *rt)
{
	struct net *net = cfg->rc_nlinfo.nl_net;
	struct mpls_nh *nh = rt->rt_nh;
	int err;
	int i;

	if (!nh)
		return -ENOMEM;

	nh->nh_labels = cfg->rc_output_labels;
	for (i = 0; i < nh->nh_labels; i++)
		nh->nh_label[i] = cfg->rc_output_label[i];

	nh->nh_via_table = cfg->rc_via_table;
	memcpy(__mpls_nh_via(rt, nh), cfg->rc_via, cfg->rc_via_alen);
	nh->nh_via_alen = cfg->rc_via_alen;

	err = mpls_nh_assign_dev(net, rt, nh, cfg->rc_ifindex);
	if (err)
		goto errout;

	if (nh->nh_flags & (RTNH_F_DEAD | RTNH_F_LINKDOWN))
		rt->rt_nhn_alive--;

	return 0;

errout:
	return err;
}