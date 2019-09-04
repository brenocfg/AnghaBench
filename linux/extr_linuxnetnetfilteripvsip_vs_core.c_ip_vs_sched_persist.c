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
typedef  union nf_inet_addr {int ip; } const nf_inet_addr ;
struct sk_buff {int /*<<< orphan*/  mark; } ;
struct ip_vs_service {int netmask; scalar_t__ port; int flags; int /*<<< orphan*/  af; int /*<<< orphan*/  ipvs; int /*<<< orphan*/  timeout; int /*<<< orphan*/  scheduler; scalar_t__ fwmark; } ;
struct ip_vs_scheduler {struct ip_vs_dest* (* schedule ) (struct ip_vs_service*,struct sk_buff*,struct ip_vs_iphdr*) ;} ;
struct ip_vs_iphdr {int protocol; union nf_inet_addr const saddr; union nf_inet_addr const daddr; } ;
struct ip_vs_dest {scalar_t__ port; int /*<<< orphan*/  addr; int /*<<< orphan*/  af; } ;
struct ip_vs_conn_param {int /*<<< orphan*/  pe_data; } ;
struct ip_vs_conn {struct ip_vs_dest* dest; int /*<<< orphan*/  timeout; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 scalar_t__ FTPPORT ; 
 int IPPROTO_IP ; 
 int IPPROTO_UDP ; 
 unsigned int IP_VS_CONN_F_ONE_PACKET ; 
 unsigned int IP_VS_CONN_F_TEMPLATE ; 
 int /*<<< orphan*/  IP_VS_DBG (int,char*) ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,union nf_inet_addr const*) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IP_VS_SVC_F_ONEPACKET ; 
 int htonl (scalar_t__) ; 
 int /*<<< orphan*/  ip_vs_check_template (struct ip_vs_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_vs_conn_fill_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,union nf_inet_addr const*,scalar_t__,union nf_inet_addr const*,scalar_t__,struct ip_vs_conn_param*) ; 
 scalar_t__ ip_vs_conn_fill_param_persist (struct ip_vs_service*,struct sk_buff*,int,union nf_inet_addr const*,int /*<<< orphan*/ ,union nf_inet_addr const*,scalar_t__,struct ip_vs_conn_param*) ; 
 struct ip_vs_conn* ip_vs_conn_new (struct ip_vs_conn_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,unsigned int,struct ip_vs_dest*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_conn_put (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_conn_stats (struct ip_vs_conn*,struct ip_vs_service*) ; 
 int /*<<< orphan*/  ip_vs_control_add (struct ip_vs_conn*,struct ip_vs_conn*) ; 
 struct ip_vs_conn* ip_vs_ct_in_get (struct ip_vs_conn_param*) ; 
 int /*<<< orphan*/  ip_vs_iph_inverse (struct ip_vs_iphdr*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 struct ip_vs_scheduler* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 struct ip_vs_dest* stub1 (struct ip_vs_service*,struct sk_buff*,struct ip_vs_iphdr*) ; 

__attribute__((used)) static struct ip_vs_conn *
ip_vs_sched_persist(struct ip_vs_service *svc,
		    struct sk_buff *skb, __be16 src_port, __be16 dst_port,
		    int *ignored, struct ip_vs_iphdr *iph)
{
	struct ip_vs_conn *cp = NULL;
	struct ip_vs_dest *dest;
	struct ip_vs_conn *ct;
	__be16 dport = 0;		/* destination port to forward */
	unsigned int flags;
	struct ip_vs_conn_param param;
	const union nf_inet_addr fwmark = { .ip = htonl(svc->fwmark) };
	union nf_inet_addr snet;	/* source network of the client,
					   after masking */
	const union nf_inet_addr *src_addr, *dst_addr;

	if (likely(!ip_vs_iph_inverse(iph))) {
		src_addr = &iph->saddr;
		dst_addr = &iph->daddr;
	} else {
		src_addr = &iph->daddr;
		dst_addr = &iph->saddr;
	}


	/* Mask saddr with the netmask to adjust template granularity */
#ifdef CONFIG_IP_VS_IPV6
	if (svc->af == AF_INET6)
		ipv6_addr_prefix(&snet.in6, &src_addr->in6,
				 (__force __u32) svc->netmask);
	else
#endif
		snet.ip = src_addr->ip & svc->netmask;

	IP_VS_DBG_BUF(6, "p-schedule: src %s:%u dest %s:%u "
		      "mnet %s\n",
		      IP_VS_DBG_ADDR(svc->af, src_addr), ntohs(src_port),
		      IP_VS_DBG_ADDR(svc->af, dst_addr), ntohs(dst_port),
		      IP_VS_DBG_ADDR(svc->af, &snet));

	/*
	 * As far as we know, FTP is a very complicated network protocol, and
	 * it uses control connection and data connections. For active FTP,
	 * FTP server initialize data connection to the client, its source port
	 * is often 20. For passive FTP, FTP server tells the clients the port
	 * that it passively listens to,  and the client issues the data
	 * connection. In the tunneling or direct routing mode, the load
	 * balancer is on the client-to-server half of connection, the port
	 * number is unknown to the load balancer. So, a conn template like
	 * <caddr, 0, vaddr, 0, daddr, 0> is created for persistent FTP
	 * service, and a template like <caddr, 0, vaddr, vport, daddr, dport>
	 * is created for other persistent services.
	 */
	{
		int protocol = iph->protocol;
		const union nf_inet_addr *vaddr = dst_addr;
		__be16 vport = 0;

		if (dst_port == svc->port) {
			/* non-FTP template:
			 * <protocol, caddr, 0, vaddr, vport, daddr, dport>
			 * FTP template:
			 * <protocol, caddr, 0, vaddr, 0, daddr, 0>
			 */
			if (svc->port != FTPPORT)
				vport = dst_port;
		} else {
			/* Note: persistent fwmark-based services and
			 * persistent port zero service are handled here.
			 * fwmark template:
			 * <IPPROTO_IP,caddr,0,fwmark,0,daddr,0>
			 * port zero template:
			 * <protocol,caddr,0,vaddr,0,daddr,0>
			 */
			if (svc->fwmark) {
				protocol = IPPROTO_IP;
				vaddr = &fwmark;
			}
		}
		/* return *ignored = -1 so NF_DROP can be used */
		if (ip_vs_conn_fill_param_persist(svc, skb, protocol, &snet, 0,
						  vaddr, vport, &param) < 0) {
			*ignored = -1;
			return NULL;
		}
	}

	/* Check if a template already exists */
	ct = ip_vs_ct_in_get(&param);
	if (!ct || !ip_vs_check_template(ct, NULL)) {
		struct ip_vs_scheduler *sched;

		/*
		 * No template found or the dest of the connection
		 * template is not available.
		 * return *ignored=0 i.e. ICMP and NF_DROP
		 */
		sched = rcu_dereference(svc->scheduler);
		if (sched) {
			/* read svc->sched_data after svc->scheduler */
			smp_rmb();
			dest = sched->schedule(svc, skb, iph);
		} else {
			dest = NULL;
		}
		if (!dest) {
			IP_VS_DBG(1, "p-schedule: no dest found.\n");
			kfree(param.pe_data);
			*ignored = 0;
			return NULL;
		}

		if (dst_port == svc->port && svc->port != FTPPORT)
			dport = dest->port;

		/* Create a template
		 * This adds param.pe_data to the template,
		 * and thus param.pe_data will be destroyed
		 * when the template expires */
		ct = ip_vs_conn_new(&param, dest->af, &dest->addr, dport,
				    IP_VS_CONN_F_TEMPLATE, dest, skb->mark);
		if (ct == NULL) {
			kfree(param.pe_data);
			*ignored = -1;
			return NULL;
		}

		ct->timeout = svc->timeout;
	} else {
		/* set destination with the found template */
		dest = ct->dest;
		kfree(param.pe_data);
	}

	dport = dst_port;
	if (dport == svc->port && dest->port)
		dport = dest->port;

	flags = (svc->flags & IP_VS_SVC_F_ONEPACKET
		 && iph->protocol == IPPROTO_UDP) ?
		IP_VS_CONN_F_ONE_PACKET : 0;

	/*
	 *    Create a new connection according to the template
	 */
	ip_vs_conn_fill_param(svc->ipvs, svc->af, iph->protocol, src_addr,
			      src_port, dst_addr, dst_port, &param);

	cp = ip_vs_conn_new(&param, dest->af, &dest->addr, dport, flags, dest,
			    skb->mark);
	if (cp == NULL) {
		ip_vs_conn_put(ct);
		*ignored = -1;
		return NULL;
	}

	/*
	 *    Add its control
	 */
	ip_vs_control_add(cp, ct);
	ip_vs_conn_put(ct);

	ip_vs_conn_stats(cp, svc);
	return cp;
}