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
struct sk_buff {int /*<<< orphan*/  mark; TYPE_1__* dev; } ;
struct ip_vs_service {int flags; scalar_t__ port; int /*<<< orphan*/  af; int /*<<< orphan*/  ipvs; int /*<<< orphan*/  scheduler; int /*<<< orphan*/  fwmark; } ;
struct ip_vs_scheduler {struct ip_vs_dest* (* schedule ) (struct ip_vs_service*,struct sk_buff*,struct ip_vs_iphdr*) ;} ;
struct ip_vs_protocol {int /*<<< orphan*/  conn_in_get; } ;
struct ip_vs_proto_data {struct ip_vs_protocol* pp; } ;
struct ip_vs_iphdr {scalar_t__ protocol; int /*<<< orphan*/  off; int /*<<< orphan*/  hdr_flags; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; int /*<<< orphan*/  len; } ;
struct ip_vs_dest {scalar_t__ port; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; } ;
struct ip_vs_conn_param {int dummy; } ;
struct ip_vs_conn {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  flags; int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; int /*<<< orphan*/  daf; int /*<<< orphan*/  vport; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  af; int /*<<< orphan*/  cport; int /*<<< orphan*/  caddr; } ;
typedef  int /*<<< orphan*/  _ports ;
typedef  scalar_t__ __be16 ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 scalar_t__ FTPDATA ; 
 int IFF_LOOPBACK ; 
 struct ip_vs_conn* INDIRECT_CALL_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,struct ip_vs_iphdr*) ; 
 scalar_t__ IPPROTO_UDP ; 
 unsigned int IP_VS_CONN_F_ONE_PACKET ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*) ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_VS_DBG_PKT (int,int /*<<< orphan*/ ,struct ip_vs_protocol*,struct sk_buff*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IP_VS_HDR_INVERSE ; 
 int IP_VS_SVC_F_ONEPACKET ; 
 int IP_VS_SVC_F_PERSISTENT ; 
 int /*<<< orphan*/  __ip_vs_conn_put (struct ip_vs_conn*) ; 
 scalar_t__* frag_safe_skb_hp (struct sk_buff*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  ip_vs_conn_fill_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void const*,scalar_t__,void const*,scalar_t__,struct ip_vs_conn_param*) ; 
 int /*<<< orphan*/  ip_vs_conn_in_get_proto ; 
 struct ip_vs_conn* ip_vs_conn_new (struct ip_vs_conn_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,unsigned int,struct ip_vs_dest*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_conn_stats (struct ip_vs_conn*,struct ip_vs_service*) ; 
 int /*<<< orphan*/  ip_vs_fwd_tag (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_iph_inverse (struct ip_vs_iphdr*) ; 
 struct ip_vs_conn* ip_vs_sched_persist (struct ip_vs_service*,struct sk_buff*,scalar_t__,scalar_t__,int*,struct ip_vs_iphdr*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct ip_vs_scheduler* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 struct ip_vs_dest* stub1 (struct ip_vs_service*,struct sk_buff*,struct ip_vs_iphdr*) ; 

struct ip_vs_conn *
ip_vs_schedule(struct ip_vs_service *svc, struct sk_buff *skb,
	       struct ip_vs_proto_data *pd, int *ignored,
	       struct ip_vs_iphdr *iph)
{
	struct ip_vs_protocol *pp = pd->pp;
	struct ip_vs_conn *cp = NULL;
	struct ip_vs_scheduler *sched;
	struct ip_vs_dest *dest;
	__be16 _ports[2], *pptr, cport, vport;
	const void *caddr, *vaddr;
	unsigned int flags;

	*ignored = 1;
	/*
	 * IPv6 frags, only the first hit here.
	 */
	pptr = frag_safe_skb_hp(skb, iph->len, sizeof(_ports), _ports);
	if (pptr == NULL)
		return NULL;

	if (likely(!ip_vs_iph_inverse(iph))) {
		cport = pptr[0];
		caddr = &iph->saddr;
		vport = pptr[1];
		vaddr = &iph->daddr;
	} else {
		cport = pptr[1];
		caddr = &iph->daddr;
		vport = pptr[0];
		vaddr = &iph->saddr;
	}

	/*
	 * FTPDATA needs this check when using local real server.
	 * Never schedule Active FTPDATA connections from real server.
	 * For LVS-NAT they must be already created. For other methods
	 * with persistence the connection is created on SYN+ACK.
	 */
	if (cport == FTPDATA) {
		IP_VS_DBG_PKT(12, svc->af, pp, skb, iph->off,
			      "Not scheduling FTPDATA");
		return NULL;
	}

	/*
	 *    Do not schedule replies from local real server.
	 */
	if ((!skb->dev || skb->dev->flags & IFF_LOOPBACK)) {
		iph->hdr_flags ^= IP_VS_HDR_INVERSE;
		cp = INDIRECT_CALL_1(pp->conn_in_get,
				     ip_vs_conn_in_get_proto, svc->ipvs,
				     svc->af, skb, iph);
		iph->hdr_flags ^= IP_VS_HDR_INVERSE;

		if (cp) {
			IP_VS_DBG_PKT(12, svc->af, pp, skb, iph->off,
				      "Not scheduling reply for existing"
				      " connection");
			__ip_vs_conn_put(cp);
			return NULL;
		}
	}

	/*
	 *    Persistent service
	 */
	if (svc->flags & IP_VS_SVC_F_PERSISTENT)
		return ip_vs_sched_persist(svc, skb, cport, vport, ignored,
					   iph);

	*ignored = 0;

	/*
	 *    Non-persistent service
	 */
	if (!svc->fwmark && vport != svc->port) {
		if (!svc->port)
			pr_err("Schedule: port zero only supported "
			       "in persistent services, "
			       "check your ipvs configuration\n");
		return NULL;
	}

	sched = rcu_dereference(svc->scheduler);
	if (sched) {
		/* read svc->sched_data after svc->scheduler */
		smp_rmb();
		dest = sched->schedule(svc, skb, iph);
	} else {
		dest = NULL;
	}
	if (dest == NULL) {
		IP_VS_DBG(1, "Schedule: no dest found.\n");
		return NULL;
	}

	flags = (svc->flags & IP_VS_SVC_F_ONEPACKET
		 && iph->protocol == IPPROTO_UDP) ?
		IP_VS_CONN_F_ONE_PACKET : 0;

	/*
	 *    Create a connection entry.
	 */
	{
		struct ip_vs_conn_param p;

		ip_vs_conn_fill_param(svc->ipvs, svc->af, iph->protocol,
				      caddr, cport, vaddr, vport, &p);
		cp = ip_vs_conn_new(&p, dest->af, &dest->addr,
				    dest->port ? dest->port : vport,
				    flags, dest, skb->mark);
		if (!cp) {
			*ignored = -1;
			return NULL;
		}
	}

	IP_VS_DBG_BUF(6, "Schedule fwd:%c c:%s:%u v:%s:%u "
		      "d:%s:%u conn->flags:%X conn->refcnt:%d\n",
		      ip_vs_fwd_tag(cp),
		      IP_VS_DBG_ADDR(cp->af, &cp->caddr), ntohs(cp->cport),
		      IP_VS_DBG_ADDR(cp->af, &cp->vaddr), ntohs(cp->vport),
		      IP_VS_DBG_ADDR(cp->daf, &cp->daddr), ntohs(cp->dport),
		      cp->flags, refcount_read(&cp->refcnt));

	ip_vs_conn_stats(cp, svc);
	return cp;
}