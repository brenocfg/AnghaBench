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
struct net_device {int dummy; } ;
struct dsa_switch_tree {TYPE_1__* pd; } ;
struct dsa_switch_ops {int dummy; } ;
struct dsa_switch {int index; void* priv; struct dsa_switch_ops const* ops; struct dsa_chip_data* cd; struct dsa_switch_tree* dst; } ;
struct dsa_chip_data {int /*<<< orphan*/  sw_addr; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct dsa_chip_data* chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_MAX_PORTS ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct dsa_switch* ERR_PTR (int) ; 
 struct dsa_switch* dsa_switch_alloc (struct device*,int /*<<< orphan*/ ) ; 
 struct dsa_switch_ops* dsa_switch_probe (struct device*,struct device*,int /*<<< orphan*/ ,char const**,void**) ; 
 int dsa_switch_setup_one (struct dsa_switch*,struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int,char const*) ; 

__attribute__((used)) static struct dsa_switch *
dsa_switch_setup(struct dsa_switch_tree *dst, struct net_device *master,
		 int index, struct device *parent, struct device *host_dev)
{
	struct dsa_chip_data *cd = dst->pd->chip + index;
	const struct dsa_switch_ops *ops;
	struct dsa_switch *ds;
	int ret;
	const char *name;
	void *priv;

	/*
	 * Probe for switch model.
	 */
	ops = dsa_switch_probe(parent, host_dev, cd->sw_addr, &name, &priv);
	if (!ops) {
		netdev_err(master, "[%d]: could not detect attached switch\n",
			   index);
		return ERR_PTR(-EINVAL);
	}
	netdev_info(master, "[%d]: detected a %s switch\n",
		    index, name);


	/*
	 * Allocate and initialise switch state.
	 */
	ds = dsa_switch_alloc(parent, DSA_MAX_PORTS);
	if (!ds)
		return ERR_PTR(-ENOMEM);

	ds->dst = dst;
	ds->index = index;
	ds->cd = cd;
	ds->ops = ops;
	ds->priv = priv;

	ret = dsa_switch_setup_one(ds, master);
	if (ret)
		return ERR_PTR(ret);

	return ds;
}