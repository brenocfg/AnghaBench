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

/* Variables and functions */
 int /*<<< orphan*/  batadv_debugfs_del_meshif (struct net_device*) ; 
 int /*<<< orphan*/  batadv_mesh_free (struct net_device*) ; 
 int /*<<< orphan*/  rcu_barrier () ; 

__attribute__((used)) static void batadv_softif_free(struct net_device *dev)
{
	batadv_debugfs_del_meshif(dev);
	batadv_mesh_free(dev);

	/* some scheduled RCU callbacks need the bat_priv struct to accomplish
	 * their tasks. Wait for them all to be finished before freeing the
	 * netdev and its private data (bat_priv)
	 */
	rcu_barrier();
}