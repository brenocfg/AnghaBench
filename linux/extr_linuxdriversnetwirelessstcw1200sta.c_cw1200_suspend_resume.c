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
struct wsm_suspend_resume {scalar_t__ stop; int /*<<< orphan*/  link_id; scalar_t__ multicast; } ;
struct cw1200_common {int tx_multicast; int join_dtim_period; int beacon_int; int /*<<< orphan*/  ps_state_lock; int /*<<< orphan*/  mcast_timeout; scalar_t__ buffered_multicasts; scalar_t__ aid0_bit_set; int /*<<< orphan*/  pm_state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  cw1200_bh_wakeup (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_pm_stay_awake (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cw1200_ps_notify (struct cw1200_common*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void cw1200_suspend_resume(struct cw1200_common *priv,
			  struct wsm_suspend_resume *arg)
{
	pr_debug("[AP] %s: %s\n",
		 arg->stop ? "stop" : "start",
		 arg->multicast ? "broadcast" : "unicast");

	if (arg->multicast) {
		bool cancel_tmo = false;
		spin_lock_bh(&priv->ps_state_lock);
		if (arg->stop) {
			priv->tx_multicast = false;
		} else {
			/* Firmware sends this indication every DTIM if there
			 * is a STA in powersave connected. There is no reason
			 * to suspend, following wakeup will consume much more
			 * power than it could be saved.
			 */
			cw1200_pm_stay_awake(&priv->pm_state,
					     priv->join_dtim_period *
					     (priv->beacon_int + 20) * HZ / 1024);
			priv->tx_multicast = (priv->aid0_bit_set &&
					      priv->buffered_multicasts);
			if (priv->tx_multicast) {
				cancel_tmo = true;
				cw1200_bh_wakeup(priv);
			}
		}
		spin_unlock_bh(&priv->ps_state_lock);
		if (cancel_tmo)
			del_timer_sync(&priv->mcast_timeout);
	} else {
		spin_lock_bh(&priv->ps_state_lock);
		cw1200_ps_notify(priv, arg->link_id, arg->stop);
		spin_unlock_bh(&priv->ps_state_lock);
		if (!arg->stop)
			cw1200_bh_wakeup(priv);
	}
	return;
}