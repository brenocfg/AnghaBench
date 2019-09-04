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
struct batadv_tp_vars {int /*<<< orphan*/  timer; TYPE_1__* bat_priv; int /*<<< orphan*/  list; int /*<<< orphan*/  finish_work; } ;
struct batadv_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tp_num; int /*<<< orphan*/  tp_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_tp_vars_put (struct batadv_tp_vars*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_tp_sender_cleanup(struct batadv_priv *bat_priv,
				     struct batadv_tp_vars *tp_vars)
{
	cancel_delayed_work(&tp_vars->finish_work);

	spin_lock_bh(&tp_vars->bat_priv->tp_list_lock);
	hlist_del_rcu(&tp_vars->list);
	spin_unlock_bh(&tp_vars->bat_priv->tp_list_lock);

	/* drop list reference */
	batadv_tp_vars_put(tp_vars);

	atomic_dec(&tp_vars->bat_priv->tp_num);

	/* kill the timer and remove its reference */
	del_timer_sync(&tp_vars->timer);
	/* the worker might have rearmed itself therefore we kill it again. Note
	 * that if the worker should run again before invoking the following
	 * del_timer(), it would not re-arm itself once again because the status
	 * is OFF now
	 */
	del_timer(&tp_vars->timer);
	batadv_tp_vars_put(tp_vars);
}