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
struct net_device {int /*<<< orphan*/ * ethtool_ops; struct dsa_port* dsa_ptr; } ;
struct dsa_port {int /*<<< orphan*/ * orig_ethtool_ops; } ;

/* Variables and functions */

__attribute__((used)) static void dsa_master_ethtool_teardown(struct net_device *dev)
{
	struct dsa_port *cpu_dp = dev->dsa_ptr;

	dev->ethtool_ops = cpu_dp->orig_ethtool_ops;
	cpu_dp->orig_ethtool_ops = NULL;
}