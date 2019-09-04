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
struct l2tp_tunnel {scalar_t__ version; int /*<<< orphan*/  l2tp_net; int /*<<< orphan*/  hlist_lock; } ;
struct l2tp_session {int /*<<< orphan*/  global_hlist; int /*<<< orphan*/  hlist; struct l2tp_tunnel* tunnel; } ;
struct l2tp_net {int /*<<< orphan*/  l2tp_session_hlist_lock; } ;

/* Variables and functions */
 scalar_t__ L2TP_HDR_VER_2 ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 struct l2tp_net* l2tp_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void __l2tp_session_unhash(struct l2tp_session *session)
{
	struct l2tp_tunnel *tunnel = session->tunnel;

	/* Remove the session from core hashes */
	if (tunnel) {
		/* Remove from the per-tunnel hash */
		write_lock_bh(&tunnel->hlist_lock);
		hlist_del_init(&session->hlist);
		write_unlock_bh(&tunnel->hlist_lock);

		/* For L2TPv3 we have a per-net hash: remove from there, too */
		if (tunnel->version != L2TP_HDR_VER_2) {
			struct l2tp_net *pn = l2tp_pernet(tunnel->l2tp_net);
			spin_lock_bh(&pn->l2tp_session_hlist_lock);
			hlist_del_init_rcu(&session->global_hlist);
			spin_unlock_bh(&pn->l2tp_session_hlist_lock);
			synchronize_rcu();
		}
	}
}