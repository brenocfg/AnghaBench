#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ protocol; } ;
struct tc_cls_matchall_offload {int /*<<< orphan*/  cookie; int /*<<< orphan*/  exts; TYPE_1__ common; } ;
struct tc_action {int dummy; } ;
struct net_device {int dummy; } ;
struct dsa_switch {TYPE_2__* ops; } ;
struct dsa_slave_priv {int /*<<< orphan*/  mall_tc_list; } ;
struct dsa_port {int /*<<< orphan*/  index; struct dsa_switch* ds; } ;
struct dsa_mall_mirror_tc_entry {int ingress; int /*<<< orphan*/  to_local_port; } ;
struct dsa_mall_tc_entry {int /*<<< orphan*/  list; struct dsa_mall_mirror_tc_entry mirror; int /*<<< orphan*/  type; int /*<<< orphan*/  cookie; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_4__ {int (* port_mirror_add ) (struct dsa_switch*,int /*<<< orphan*/ ,struct dsa_mall_mirror_tc_entry*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_PORT_MALL_MIRROR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_P_ALL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dsa_slave_dev_check (struct net_device*) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ is_tcf_mirred_egress_mirror (struct tc_action const*) ; 
 int /*<<< orphan*/  kfree (struct dsa_mall_tc_entry*) ; 
 struct dsa_mall_tc_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dsa_slave_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct dsa_switch*,int /*<<< orphan*/ ,struct dsa_mall_mirror_tc_entry*,int) ; 
 struct tc_action* tcf_exts_first_action (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_exts_has_one_action (int /*<<< orphan*/ ) ; 
 struct net_device* tcf_mirred_dev (struct tc_action const*) ; 

__attribute__((used)) static int dsa_slave_add_cls_matchall(struct net_device *dev,
				      struct tc_cls_matchall_offload *cls,
				      bool ingress)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_slave_priv *p = netdev_priv(dev);
	struct dsa_mall_tc_entry *mall_tc_entry;
	__be16 protocol = cls->common.protocol;
	struct dsa_switch *ds = dp->ds;
	struct net_device *to_dev;
	const struct tc_action *a;
	struct dsa_port *to_dp;
	int err = -EOPNOTSUPP;

	if (!ds->ops->port_mirror_add)
		return err;

	if (!tcf_exts_has_one_action(cls->exts))
		return err;

	a = tcf_exts_first_action(cls->exts);

	if (is_tcf_mirred_egress_mirror(a) && protocol == htons(ETH_P_ALL)) {
		struct dsa_mall_mirror_tc_entry *mirror;

		to_dev = tcf_mirred_dev(a);
		if (!to_dev)
			return -EINVAL;

		if (!dsa_slave_dev_check(to_dev))
			return -EOPNOTSUPP;

		mall_tc_entry = kzalloc(sizeof(*mall_tc_entry), GFP_KERNEL);
		if (!mall_tc_entry)
			return -ENOMEM;

		mall_tc_entry->cookie = cls->cookie;
		mall_tc_entry->type = DSA_PORT_MALL_MIRROR;
		mirror = &mall_tc_entry->mirror;

		to_dp = dsa_slave_to_port(to_dev);

		mirror->to_local_port = to_dp->index;
		mirror->ingress = ingress;

		err = ds->ops->port_mirror_add(ds, dp->index, mirror, ingress);
		if (err) {
			kfree(mall_tc_entry);
			return err;
		}

		list_add_tail(&mall_tc_entry->list, &p->mall_tc_list);
	}

	return 0;
}