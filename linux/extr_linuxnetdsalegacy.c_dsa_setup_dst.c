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
struct net_device {int dummy; } ;
struct dsa_switch_tree {TYPE_2__* cpu_dp; struct dsa_switch** ds; struct dsa_platform_data* pd; } ;
struct dsa_switch {int dummy; } ;
struct dsa_platform_data {int nr_chips; TYPE_1__* chip; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  master; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct dsa_switch*) ; 
 int /*<<< orphan*/  PTR_ERR (struct dsa_switch*) ; 
 int dsa_master_setup (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct dsa_switch* dsa_switch_setup (struct dsa_switch_tree*,struct net_device*,int,struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_setup_dst(struct dsa_switch_tree *dst, struct net_device *dev,
			 struct device *parent, struct dsa_platform_data *pd)
{
	int i;
	unsigned configured = 0;

	dst->pd = pd;

	for (i = 0; i < pd->nr_chips; i++) {
		struct dsa_switch *ds;

		ds = dsa_switch_setup(dst, dev, i, parent, pd->chip[i].host_dev);
		if (IS_ERR(ds)) {
			netdev_err(dev, "[%d]: couldn't create dsa switch instance (error %ld)\n",
				   i, PTR_ERR(ds));
			continue;
		}

		dst->ds[i] = ds;

		++configured;
	}

	/*
	 * If no switch was found, exit cleanly
	 */
	if (!configured)
		return -EPROBE_DEFER;

	return dsa_master_setup(dst->cpu_dp->master, dst->cpu_dp);
}