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
struct TYPE_2__ {int /*<<< orphan*/  commit_lock; } ;
struct batadv_priv {TYPE_1__ tt; int /*<<< orphan*/  packet_size_max; } ;

/* Variables and functions */
 int BATADV_TT_LOCAL_TIMEOUT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_info ; 
 int /*<<< orphan*/  batadv_tt_local_commit_changes_nolock (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_tt_local_purge (struct batadv_priv*,int) ; 
 int /*<<< orphan*/  batadv_tt_local_purge_pending_clients (struct batadv_priv*) ; 
 int batadv_tt_local_table_transmit_size (struct batadv_priv*) ; 
 int /*<<< orphan*/  net_ratelimited_function (int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 struct batadv_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void batadv_tt_local_resize_to_mtu(struct net_device *soft_iface)
{
	struct batadv_priv *bat_priv = netdev_priv(soft_iface);
	int packet_size_max = atomic_read(&bat_priv->packet_size_max);
	int table_size, timeout = BATADV_TT_LOCAL_TIMEOUT / 2;
	bool reduced = false;

	spin_lock_bh(&bat_priv->tt.commit_lock);

	while (true) {
		table_size = batadv_tt_local_table_transmit_size(bat_priv);
		if (packet_size_max >= table_size)
			break;

		batadv_tt_local_purge(bat_priv, timeout);
		batadv_tt_local_purge_pending_clients(bat_priv);

		timeout /= 2;
		reduced = true;
		net_ratelimited_function(batadv_info, soft_iface,
					 "Forced to purge local tt entries to fit new maximum fragment MTU (%i)\n",
					 packet_size_max);
	}

	/* commit these changes immediately, to avoid synchronization problem
	 * with the TTVN
	 */
	if (reduced)
		batadv_tt_local_commit_changes_nolock(bat_priv);

	spin_unlock_bh(&bat_priv->tt.commit_lock);
}