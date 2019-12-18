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
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_port {int /*<<< orphan*/  index; struct dsa_switch* ds; } ;
struct TYPE_2__ {scalar_t__ (* get_sset_count ) (struct dsa_switch*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ETH_SS_STATS ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 scalar_t__ stub1 (struct dsa_switch*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dsa_slave_get_sset_count(struct net_device *dev, int sset)
{
	struct dsa_port *dp = dsa_slave_to_port(dev);
	struct dsa_switch *ds = dp->ds;

	if (sset == ETH_SS_STATS) {
		int count;

		count = 4;
		if (ds->ops->get_sset_count)
			count += ds->ops->get_sset_count(ds, dp->index, sset);

		return count;
	}

	return -EOPNOTSUPP;
}