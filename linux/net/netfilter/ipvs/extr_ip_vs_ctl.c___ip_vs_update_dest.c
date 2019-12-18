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
struct netns_ipvs {int /*<<< orphan*/  mixed_address_family_dests; } ;
struct ip_vs_service {scalar_t__ af; scalar_t__ port; int /*<<< orphan*/  scheduler; int /*<<< orphan*/  num_dests; int /*<<< orphan*/  destinations; struct netns_ipvs* ipvs; } ;
struct ip_vs_scheduler {int /*<<< orphan*/  (* upd_dest ) (struct ip_vs_service*,struct ip_vs_dest*) ;int /*<<< orphan*/  (* add_dest ) (struct ip_vs_service*,struct ip_vs_dest*) ;} ;
struct ip_vs_dest_user_kern {scalar_t__ af; int weight; int conn_flags; scalar_t__ tun_type; scalar_t__ tun_port; scalar_t__ u_threshold; int /*<<< orphan*/  l_threshold; int /*<<< orphan*/  tun_flags; } ;
struct ip_vs_dest {scalar_t__ af; scalar_t__ tun_type; scalar_t__ tun_port; scalar_t__ u_threshold; int /*<<< orphan*/  n_list; int /*<<< orphan*/  stats; int /*<<< orphan*/  dst_lock; int /*<<< orphan*/  l_threshold; int /*<<< orphan*/  flags; int /*<<< orphan*/  svc; int /*<<< orphan*/  conn_flags; int /*<<< orphan*/  tun_flags; int /*<<< orphan*/  weight; int /*<<< orphan*/  last_weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ FTPPORT ; 
 int IP_VS_CONN_F_DEST_MASK ; 
 int IP_VS_CONN_F_FWD_MASK ; 
 int IP_VS_CONN_F_INACTIVE ; 
 int IP_VS_CONN_F_MASQ ; 
 int IP_VS_CONN_F_NOOUTPUT ; 
 int /*<<< orphan*/  IP_VS_DEST_F_AVAILABLE ; 
 int /*<<< orphan*/  IP_VS_DEST_F_OVERLOAD ; 
 int IP_VS_DFWD_METHOD (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  __ip_vs_bind_svc (struct ip_vs_dest*,struct ip_vs_service*) ; 
 int /*<<< orphan*/  __ip_vs_dst_cache_reset (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  __ip_vs_svc_put (struct ip_vs_service*,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ip_vs_register_conntrack (struct ip_vs_service*) ; 
 int /*<<< orphan*/  ip_vs_rs_hash (struct netns_ipvs*,struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ip_vs_rs_unhash (struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ip_vs_start_estimator (struct netns_ipvs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_zero_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ip_vs_service*,struct ip_vs_dest*) ; 
 int /*<<< orphan*/  stub2 (struct ip_vs_service*,struct ip_vs_dest*) ; 

__attribute__((used)) static void
__ip_vs_update_dest(struct ip_vs_service *svc, struct ip_vs_dest *dest,
		    struct ip_vs_dest_user_kern *udest, int add)
{
	struct netns_ipvs *ipvs = svc->ipvs;
	struct ip_vs_service *old_svc;
	struct ip_vs_scheduler *sched;
	int conn_flags;

	/* We cannot modify an address and change the address family */
	BUG_ON(!add && udest->af != dest->af);

	if (add && udest->af != svc->af)
		ipvs->mixed_address_family_dests++;

	/* keep the last_weight with latest non-0 weight */
	if (add || udest->weight != 0)
		atomic_set(&dest->last_weight, udest->weight);

	/* set the weight and the flags */
	atomic_set(&dest->weight, udest->weight);
	conn_flags = udest->conn_flags & IP_VS_CONN_F_DEST_MASK;
	conn_flags |= IP_VS_CONN_F_INACTIVE;

	/* Need to rehash? */
	if ((udest->conn_flags & IP_VS_CONN_F_FWD_MASK) !=
	    IP_VS_DFWD_METHOD(dest) ||
	    udest->tun_type != dest->tun_type ||
	    udest->tun_port != dest->tun_port)
		ip_vs_rs_unhash(dest);

	/* set the tunnel info */
	dest->tun_type = udest->tun_type;
	dest->tun_port = udest->tun_port;
	dest->tun_flags = udest->tun_flags;

	/* set the IP_VS_CONN_F_NOOUTPUT flag if not masquerading/NAT */
	if ((conn_flags & IP_VS_CONN_F_FWD_MASK) != IP_VS_CONN_F_MASQ) {
		conn_flags |= IP_VS_CONN_F_NOOUTPUT;
	} else {
		/* FTP-NAT requires conntrack for mangling */
		if (svc->port == FTPPORT)
			ip_vs_register_conntrack(svc);
	}
	atomic_set(&dest->conn_flags, conn_flags);
	/* Put the real service in rs_table if not present. */
	ip_vs_rs_hash(ipvs, dest);

	/* bind the service */
	old_svc = rcu_dereference_protected(dest->svc, 1);
	if (!old_svc) {
		__ip_vs_bind_svc(dest, svc);
	} else {
		if (old_svc != svc) {
			ip_vs_zero_stats(&dest->stats);
			__ip_vs_bind_svc(dest, svc);
			__ip_vs_svc_put(old_svc, true);
		}
	}

	/* set the dest status flags */
	dest->flags |= IP_VS_DEST_F_AVAILABLE;

	if (udest->u_threshold == 0 || udest->u_threshold > dest->u_threshold)
		dest->flags &= ~IP_VS_DEST_F_OVERLOAD;
	dest->u_threshold = udest->u_threshold;
	dest->l_threshold = udest->l_threshold;

	dest->af = udest->af;

	spin_lock_bh(&dest->dst_lock);
	__ip_vs_dst_cache_reset(dest);
	spin_unlock_bh(&dest->dst_lock);

	if (add) {
		ip_vs_start_estimator(svc->ipvs, &dest->stats);
		list_add_rcu(&dest->n_list, &svc->destinations);
		svc->num_dests++;
		sched = rcu_dereference_protected(svc->scheduler, 1);
		if (sched && sched->add_dest)
			sched->add_dest(svc, dest);
	} else {
		sched = rcu_dereference_protected(svc->scheduler, 1);
		if (sched && sched->upd_dest)
			sched->upd_dest(svc, dest);
	}
}