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
struct net_dev_channel {int linked; int ch_id; } ;
struct net_dev_context {int /*<<< orphan*/  dev; int /*<<< orphan*/  list; struct net_dev_channel tx; struct net_dev_channel rx; } ;
struct most_interface {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 struct net_dev_context* get_net_dev (struct most_interface*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  probe_disc_mt ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int comp_disconnect_channel(struct most_interface *iface,
				   int channel_idx)
{
	struct net_dev_context *nd;
	struct net_dev_channel *ch;
	unsigned long flags;
	int ret = 0;

	mutex_lock(&probe_disc_mt);
	nd = get_net_dev(iface);
	if (!nd) {
		ret = -EINVAL;
		goto unlock;
	}

	if (nd->rx.linked && channel_idx == nd->rx.ch_id) {
		ch = &nd->rx;
	} else if (nd->tx.linked && channel_idx == nd->tx.ch_id) {
		ch = &nd->tx;
	} else {
		ret = -EINVAL;
		goto unlock;
	}

	if (nd->rx.linked && nd->tx.linked) {
		spin_lock_irqsave(&list_lock, flags);
		ch->linked = false;
		spin_unlock_irqrestore(&list_lock, flags);

		/*
		 * do not call most_stop_channel() here, because channels are
		 * going to be closed in ndo_stop() after unregister_netdev()
		 */
		unregister_netdev(nd->dev);
	} else {
		spin_lock_irqsave(&list_lock, flags);
		list_del(&nd->list);
		spin_unlock_irqrestore(&list_lock, flags);

		free_netdev(nd->dev);
	}

unlock:
	mutex_unlock(&probe_disc_mt);
	return ret;
}