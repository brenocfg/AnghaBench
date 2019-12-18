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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct netns_ipvs {int dummy; } ;
struct ip_vs_sync_conn_options {int /*<<< orphan*/  out_seq; int /*<<< orphan*/  in_seq; } ;
struct ip_vs_proto_data {unsigned long* timeout_table; } ;
struct ip_vs_dest {int /*<<< orphan*/  inactconns; int /*<<< orphan*/  activeconns; } ;
struct ip_vs_conn_param {int /*<<< orphan*/  pe_data; int /*<<< orphan*/  vport; int /*<<< orphan*/  vaddr; } ;
struct ip_vs_conn {scalar_t__ dport; unsigned int flags; unsigned int state; unsigned int old_state; unsigned long timeout; int /*<<< orphan*/  in_pkts; int /*<<< orphan*/  out_seq; int /*<<< orphan*/  in_seq; int /*<<< orphan*/  lock; struct ip_vs_dest* dest; int /*<<< orphan*/  daddr; int /*<<< orphan*/  daf; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned int IP_VS_CONN_F_BACKUP_UPD_MASK ; 
 unsigned int IP_VS_CONN_F_INACTIVE ; 
 unsigned int IP_VS_CONN_F_TEMPLATE ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*) ; 
 unsigned long MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  __ip_vs_conn_put (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,union nf_inet_addr const*) ; 
 int /*<<< orphan*/  ip_vs_conn_expire_now (struct ip_vs_conn*) ; 
 struct ip_vs_conn* ip_vs_conn_in_get (struct ip_vs_conn_param*) ; 
 struct ip_vs_conn* ip_vs_conn_new (struct ip_vs_conn_param*,unsigned int,union nf_inet_addr const*,scalar_t__,unsigned int,struct ip_vs_dest*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_conn_put (struct ip_vs_conn*) ; 
 struct ip_vs_conn* ip_vs_ct_in_get (struct ip_vs_conn_param*) ; 
 struct ip_vs_dest* ip_vs_find_dest (struct netns_ipvs*,unsigned int,unsigned int,union nf_inet_addr const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 struct ip_vs_proto_data* ip_vs_proto_data_get (struct netns_ipvs*,unsigned int) ; 
 int /*<<< orphan*/  ip_vs_try_bind_dest (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_sync_threshold (struct netns_ipvs*) ; 

__attribute__((used)) static void ip_vs_proc_conn(struct netns_ipvs *ipvs, struct ip_vs_conn_param *param,
			    unsigned int flags, unsigned int state,
			    unsigned int protocol, unsigned int type,
			    const union nf_inet_addr *daddr, __be16 dport,
			    unsigned long timeout, __u32 fwmark,
			    struct ip_vs_sync_conn_options *opt)
{
	struct ip_vs_dest *dest;
	struct ip_vs_conn *cp;

	if (!(flags & IP_VS_CONN_F_TEMPLATE)) {
		cp = ip_vs_conn_in_get(param);
		if (cp && ((cp->dport != dport) ||
			   !ip_vs_addr_equal(cp->daf, &cp->daddr, daddr))) {
			if (!(flags & IP_VS_CONN_F_INACTIVE)) {
				ip_vs_conn_expire_now(cp);
				__ip_vs_conn_put(cp);
				cp = NULL;
			} else {
				/* This is the expiration message for the
				 * connection that was already replaced, so we
				 * just ignore it.
				 */
				__ip_vs_conn_put(cp);
				kfree(param->pe_data);
				return;
			}
		}
	} else {
		cp = ip_vs_ct_in_get(param);
	}

	if (cp) {
		/* Free pe_data */
		kfree(param->pe_data);

		dest = cp->dest;
		spin_lock_bh(&cp->lock);
		if ((cp->flags ^ flags) & IP_VS_CONN_F_INACTIVE &&
		    !(flags & IP_VS_CONN_F_TEMPLATE) && dest) {
			if (flags & IP_VS_CONN_F_INACTIVE) {
				atomic_dec(&dest->activeconns);
				atomic_inc(&dest->inactconns);
			} else {
				atomic_inc(&dest->activeconns);
				atomic_dec(&dest->inactconns);
			}
		}
		flags &= IP_VS_CONN_F_BACKUP_UPD_MASK;
		flags |= cp->flags & ~IP_VS_CONN_F_BACKUP_UPD_MASK;
		cp->flags = flags;
		spin_unlock_bh(&cp->lock);
		if (!dest)
			ip_vs_try_bind_dest(cp);
	} else {
		/*
		 * Find the appropriate destination for the connection.
		 * If it is not found the connection will remain unbound
		 * but still handled.
		 */
		rcu_read_lock();
		/* This function is only invoked by the synchronization
		 * code. We do not currently support heterogeneous pools
		 * with synchronization, so we can make the assumption that
		 * the svc_af is the same as the dest_af
		 */
		dest = ip_vs_find_dest(ipvs, type, type, daddr, dport,
				       param->vaddr, param->vport, protocol,
				       fwmark, flags);

		cp = ip_vs_conn_new(param, type, daddr, dport, flags, dest,
				    fwmark);
		rcu_read_unlock();
		if (!cp) {
			kfree(param->pe_data);
			IP_VS_DBG(2, "BACKUP, add new conn. failed\n");
			return;
		}
		if (!(flags & IP_VS_CONN_F_TEMPLATE))
			kfree(param->pe_data);
	}

	if (opt) {
		cp->in_seq = opt->in_seq;
		cp->out_seq = opt->out_seq;
	}
	atomic_set(&cp->in_pkts, sysctl_sync_threshold(ipvs));
	cp->state = state;
	cp->old_state = cp->state;
	/*
	 * For Ver 0 messages style
	 *  - Not possible to recover the right timeout for templates
	 *  - can not find the right fwmark
	 *    virtual service. If needed, we can do it for
	 *    non-fwmark persistent services.
	 * Ver 1 messages style.
	 *  - No problem.
	 */
	if (timeout) {
		if (timeout > MAX_SCHEDULE_TIMEOUT / HZ)
			timeout = MAX_SCHEDULE_TIMEOUT / HZ;
		cp->timeout = timeout*HZ;
	} else {
		struct ip_vs_proto_data *pd;

		pd = ip_vs_proto_data_get(ipvs, protocol);
		if (!(flags & IP_VS_CONN_F_TEMPLATE) && pd && pd->timeout_table)
			cp->timeout = pd->timeout_table[state];
		else
			cp->timeout = (3*60*HZ);
	}
	ip_vs_conn_put(cp);
}