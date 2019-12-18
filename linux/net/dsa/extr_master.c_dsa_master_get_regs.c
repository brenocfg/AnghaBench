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
struct net_device {struct dsa_port* dsa_ptr; } ;
struct ethtool_regs {int len; } ;
struct ethtool_ops {int (* get_regs_len ) (struct net_device*) ;int /*<<< orphan*/  (* get_regs ) (struct net_device*,struct ethtool_regs*,void*) ;} ;
struct ethtool_drvinfo {int /*<<< orphan*/  driver; } ;
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_port {int index; struct dsa_switch* ds; struct ethtool_ops* orig_ethtool_ops; } ;
struct TYPE_2__ {int (* get_regs_len ) (struct dsa_switch*,int) ;int /*<<< orphan*/  (* get_regs ) (struct dsa_switch*,int,struct ethtool_regs*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,struct ethtool_regs*,void*) ; 
 int stub3 (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  stub4 (struct dsa_switch*,int,struct ethtool_regs*,void*) ; 

__attribute__((used)) static void dsa_master_get_regs(struct net_device *dev,
				struct ethtool_regs *regs, void *data)
{
	struct dsa_port *cpu_dp = dev->dsa_ptr;
	const struct ethtool_ops *ops = cpu_dp->orig_ethtool_ops;
	struct dsa_switch *ds = cpu_dp->ds;
	struct ethtool_drvinfo *cpu_info;
	struct ethtool_regs *cpu_regs;
	int port = cpu_dp->index;
	int len;

	if (ops->get_regs_len && ops->get_regs) {
		len = ops->get_regs_len(dev);
		if (len < 0)
			return;
		regs->len = len;
		ops->get_regs(dev, regs, data);
		data += regs->len;
	}

	cpu_info = (struct ethtool_drvinfo *)data;
	strlcpy(cpu_info->driver, "dsa", sizeof(cpu_info->driver));
	data += sizeof(*cpu_info);
	cpu_regs = (struct ethtool_regs *)data;
	data += sizeof(*cpu_regs);

	if (ds->ops->get_regs_len && ds->ops->get_regs) {
		len = ds->ops->get_regs_len(ds, port);
		if (len < 0)
			return;
		cpu_regs->len = len;
		ds->ops->get_regs(ds, port, cpu_regs, data);
	}
}