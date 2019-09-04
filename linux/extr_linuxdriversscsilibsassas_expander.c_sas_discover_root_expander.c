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
struct sas_expander_device {int /*<<< orphan*/  level; } ;
struct domain_device {int /*<<< orphan*/  rphy; TYPE_2__* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_level; } ;
struct TYPE_4__ {TYPE_1__ disc; } ;

/* Variables and functions */
 struct sas_expander_device* rphy_to_expander_device (int /*<<< orphan*/ ) ; 
 int sas_discover_expander (struct domain_device*) ; 
 int /*<<< orphan*/  sas_ex_bfs_disc (TYPE_2__*) ; 
 int sas_rphy_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_rphy_remove (int /*<<< orphan*/ ) ; 

int sas_discover_root_expander(struct domain_device *dev)
{
	int res;
	struct sas_expander_device *ex = rphy_to_expander_device(dev->rphy);

	res = sas_rphy_add(dev->rphy);
	if (res)
		goto out_err;

	ex->level = dev->port->disc.max_level; /* 0 */
	res = sas_discover_expander(dev);
	if (res)
		goto out_err2;

	sas_ex_bfs_disc(dev->port);

	return res;

out_err2:
	sas_rphy_remove(dev->rphy);
out_err:
	return res;
}