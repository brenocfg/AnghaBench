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
struct net_bridge_port {scalar_t__ br; int /*<<< orphan*/  backup_port; int /*<<< orphan*/  backup_redirected_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EINVAL ; 
 int ENOENT ; 
 struct net_bridge_port* br_port_get_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  netif_is_bridge_port (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_bridge_port*) ; 
 struct net_bridge_port* rtnl_dereference (int /*<<< orphan*/ ) ; 

int nbp_backup_change(struct net_bridge_port *p,
		      struct net_device *backup_dev)
{
	struct net_bridge_port *old_backup = rtnl_dereference(p->backup_port);
	struct net_bridge_port *backup_p = NULL;

	ASSERT_RTNL();

	if (backup_dev) {
		if (!netif_is_bridge_port(backup_dev))
			return -ENOENT;

		backup_p = br_port_get_rtnl(backup_dev);
		if (backup_p->br != p->br)
			return -EINVAL;
	}

	if (p == backup_p)
		return -EINVAL;

	if (old_backup == backup_p)
		return 0;

	/* if the backup link is already set, clear it */
	if (old_backup)
		old_backup->backup_redirected_cnt--;

	if (backup_p)
		backup_p->backup_redirected_cnt++;
	rcu_assign_pointer(p->backup_port, backup_p);

	return 0;
}