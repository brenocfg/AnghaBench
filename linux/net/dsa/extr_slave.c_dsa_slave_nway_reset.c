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
struct net_device {int dummy; } ;
struct dsa_port {int /*<<< orphan*/  pl; } ;

/* Variables and functions */
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int phylink_ethtool_nway_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_slave_nway_reset(struct net_device *dev)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);

	return phylink_ethtool_nway_reset(dp->pl);
}