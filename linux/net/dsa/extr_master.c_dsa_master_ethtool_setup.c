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
struct net_device {struct ethtool_ops* ethtool_ops; struct dsa_port* dsa_ptr; } ;
struct ethtool_ops {int /*<<< orphan*/  get_ethtool_phy_stats; int /*<<< orphan*/  get_strings; int /*<<< orphan*/  get_ethtool_stats; int /*<<< orphan*/  get_sset_count; int /*<<< orphan*/  get_regs; int /*<<< orphan*/  get_regs_len; } ;
struct dsa_switch {int /*<<< orphan*/  dev; } ;
struct dsa_port {struct ethtool_ops* orig_ethtool_ops; struct dsa_switch* ds; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ethtool_ops* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsa_master_get_ethtool_phy_stats ; 
 int /*<<< orphan*/  dsa_master_get_ethtool_stats ; 
 int /*<<< orphan*/  dsa_master_get_regs ; 
 int /*<<< orphan*/  dsa_master_get_regs_len ; 
 int /*<<< orphan*/  dsa_master_get_sset_count ; 
 int /*<<< orphan*/  dsa_master_get_strings ; 
 int /*<<< orphan*/  memcpy (struct ethtool_ops*,struct ethtool_ops*,int) ; 

__attribute__((used)) static int dsa_master_ethtool_setup(struct net_device *dev)
{
	struct dsa_port *cpu_dp = dev->dsa_ptr;
	struct dsa_switch *ds = cpu_dp->ds;
	struct ethtool_ops *ops;

	ops = devm_kzalloc(ds->dev, sizeof(*ops), GFP_KERNEL);
	if (!ops)
		return -ENOMEM;

	cpu_dp->orig_ethtool_ops = dev->ethtool_ops;
	if (cpu_dp->orig_ethtool_ops)
		memcpy(ops, cpu_dp->orig_ethtool_ops, sizeof(*ops));

	ops->get_regs_len = dsa_master_get_regs_len;
	ops->get_regs = dsa_master_get_regs;
	ops->get_sset_count = dsa_master_get_sset_count;
	ops->get_ethtool_stats = dsa_master_get_ethtool_stats;
	ops->get_strings = dsa_master_get_strings;
	ops->get_ethtool_phy_stats = dsa_master_get_ethtool_phy_stats;

	dev->ethtool_ops = ops;

	return 0;
}