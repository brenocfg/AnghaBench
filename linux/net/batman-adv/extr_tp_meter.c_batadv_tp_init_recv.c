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
struct batadv_tp_vars {int /*<<< orphan*/  timer; int /*<<< orphan*/  refcount; int /*<<< orphan*/  list; int /*<<< orphan*/  unacked_list; int /*<<< orphan*/  unacked_lock; struct batadv_priv* bat_priv; int /*<<< orphan*/  last_recv; int /*<<< orphan*/  session; int /*<<< orphan*/  role; int /*<<< orphan*/  other_end; } ;
struct batadv_priv {int /*<<< orphan*/  tp_list_lock; int /*<<< orphan*/  tp_list; int /*<<< orphan*/  tp_num; } ;
struct batadv_icmp_tp_packet {int /*<<< orphan*/  session; int /*<<< orphan*/  orig; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_TP_METER ; 
 int /*<<< orphan*/  BATADV_TP_FIRST_SEQ ; 
 int /*<<< orphan*/  BATADV_TP_MAX_NUM ; 
 int /*<<< orphan*/  BATADV_TP_RECEIVER ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*) ; 
 struct batadv_tp_vars* batadv_tp_list_find_session (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tp_receiver_shutdown ; 
 int /*<<< orphan*/  batadv_tp_reset_receiver_timer (struct batadv_tp_vars*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct batadv_tp_vars* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct batadv_tp_vars *
batadv_tp_init_recv(struct batadv_priv *bat_priv,
		    const struct batadv_icmp_tp_packet *icmp)
{
	struct batadv_tp_vars *tp_vars;

	spin_lock_bh(&bat_priv->tp_list_lock);
	tp_vars = batadv_tp_list_find_session(bat_priv, icmp->orig,
					      icmp->session);
	if (tp_vars)
		goto out_unlock;

	if (!atomic_add_unless(&bat_priv->tp_num, 1, BATADV_TP_MAX_NUM)) {
		batadv_dbg(BATADV_DBG_TP_METER, bat_priv,
			   "Meter: too many ongoing sessions, aborting (RECV)\n");
		goto out_unlock;
	}

	tp_vars = kmalloc(sizeof(*tp_vars), GFP_ATOMIC);
	if (!tp_vars)
		goto out_unlock;

	ether_addr_copy(tp_vars->other_end, icmp->orig);
	tp_vars->role = BATADV_TP_RECEIVER;
	memcpy(tp_vars->session, icmp->session, sizeof(tp_vars->session));
	tp_vars->last_recv = BATADV_TP_FIRST_SEQ;
	tp_vars->bat_priv = bat_priv;
	kref_init(&tp_vars->refcount);

	spin_lock_init(&tp_vars->unacked_lock);
	INIT_LIST_HEAD(&tp_vars->unacked_list);

	kref_get(&tp_vars->refcount);
	hlist_add_head_rcu(&tp_vars->list, &bat_priv->tp_list);

	kref_get(&tp_vars->refcount);
	timer_setup(&tp_vars->timer, batadv_tp_receiver_shutdown, 0);

	batadv_tp_reset_receiver_timer(tp_vars);

out_unlock:
	spin_unlock_bh(&bat_priv->tp_list_lock);

	return tp_vars;
}