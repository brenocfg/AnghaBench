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
struct ip_vs_proto_data {int /*<<< orphan*/  pp; int /*<<< orphan*/  appcnt; } ;
struct ip_vs_dest {int dummy; } ;
struct ip_vs_conn {scalar_t__ af; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ipvs; int /*<<< orphan*/ * packet_xmit; int /*<<< orphan*/  lock; scalar_t__ app; scalar_t__ dest; int /*<<< orphan*/  flags; int /*<<< orphan*/  fwmark; int /*<<< orphan*/  vport; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_bind_app (struct ip_vs_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_bind_dest (struct ip_vs_conn*,struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ip_vs_bind_xmit (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_bind_xmit_v6 (struct ip_vs_conn*) ; 
 struct ip_vs_dest* ip_vs_find_dest (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ip_vs_proto_data* ip_vs_proto_data_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_unbind_app (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ip_vs_try_bind_dest(struct ip_vs_conn *cp)
{
	struct ip_vs_dest *dest;

	rcu_read_lock();

	/* This function is only invoked by the synchronization code. We do
	 * not currently support heterogeneous pools with synchronization,
	 * so we can make the assumption that the svc_af is the same as the
	 * dest_af
	 */
	dest = ip_vs_find_dest(cp->ipvs, cp->af, cp->af, &cp->daddr,
			       cp->dport, &cp->vaddr, cp->vport,
			       cp->protocol, cp->fwmark, cp->flags);
	if (dest) {
		struct ip_vs_proto_data *pd;

		spin_lock_bh(&cp->lock);
		if (cp->dest) {
			spin_unlock_bh(&cp->lock);
			rcu_read_unlock();
			return;
		}

		/* Applications work depending on the forwarding method
		 * but better to reassign them always when binding dest */
		if (cp->app)
			ip_vs_unbind_app(cp);

		ip_vs_bind_dest(cp, dest);
		spin_unlock_bh(&cp->lock);

		/* Update its packet transmitter */
		cp->packet_xmit = NULL;
#ifdef CONFIG_IP_VS_IPV6
		if (cp->af == AF_INET6)
			ip_vs_bind_xmit_v6(cp);
		else
#endif
			ip_vs_bind_xmit(cp);

		pd = ip_vs_proto_data_get(cp->ipvs, cp->protocol);
		if (pd && atomic_read(&pd->appcnt))
			ip_vs_bind_app(cp, pd->pp);
	}
	rcu_read_unlock();
}