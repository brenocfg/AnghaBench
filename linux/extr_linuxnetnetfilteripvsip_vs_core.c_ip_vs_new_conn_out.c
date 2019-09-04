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
union nf_inet_addr {int ip; } ;
struct sk_buff {int dummy; } ;
struct ip_vs_service {int flags; int netmask; int /*<<< orphan*/  af; int /*<<< orphan*/  ipvs; int /*<<< orphan*/  timeout; scalar_t__ fwmark; int /*<<< orphan*/  port; union nf_inet_addr addr; } ;
struct ip_vs_iphdr {scalar_t__ protocol; union nf_inet_addr daddr; union nf_inet_addr saddr; } ;
struct ip_vs_dest {int /*<<< orphan*/  af; } ;
struct ip_vs_conn_param {int /*<<< orphan*/  pe_data; } ;
struct ip_vs_conn {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  flags; int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; int /*<<< orphan*/  af; int /*<<< orphan*/  vport; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  cport; int /*<<< orphan*/  caddr; int /*<<< orphan*/  timeout; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  EnterFunction (int) ; 
 scalar_t__ IPPROTO_UDP ; 
 unsigned int IP_VS_CONN_F_ONE_PACKET ; 
 unsigned int IP_VS_CONN_F_TEMPLATE ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IP_VS_SVC_F_ONEPACKET ; 
 int IP_VS_SVC_F_PERSISTENT ; 
 int /*<<< orphan*/  LeaveFunction (int) ; 
 int /*<<< orphan*/  ip_vs_check_template (struct ip_vs_conn*,struct ip_vs_dest*) ; 
 int /*<<< orphan*/  ip_vs_conn_fill_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,union nf_inet_addr const*,int /*<<< orphan*/ ,union nf_inet_addr const*,int /*<<< orphan*/ ,struct ip_vs_conn_param*) ; 
 scalar_t__ ip_vs_conn_fill_param_persist (struct ip_vs_service*,struct sk_buff*,scalar_t__,union nf_inet_addr*,int /*<<< orphan*/ ,union nf_inet_addr const*,int /*<<< orphan*/ ,struct ip_vs_conn_param*) ; 
 struct ip_vs_conn* ip_vs_conn_new (struct ip_vs_conn_param*,int /*<<< orphan*/ ,union nf_inet_addr const*,int /*<<< orphan*/ ,unsigned int,struct ip_vs_dest*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_conn_put (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  ip_vs_conn_stats (struct ip_vs_conn*,struct ip_vs_service*) ; 
 int /*<<< orphan*/  ip_vs_control_add (struct ip_vs_conn*,struct ip_vs_conn*) ; 
 struct ip_vs_conn* ip_vs_ct_in_get (struct ip_vs_conn_param*) ; 
 int /*<<< orphan*/  ip_vs_fwd_tag (struct ip_vs_conn*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

struct ip_vs_conn *ip_vs_new_conn_out(struct ip_vs_service *svc,
				      struct ip_vs_dest *dest,
				      struct sk_buff *skb,
				      const struct ip_vs_iphdr *iph,
				      __be16 dport,
				      __be16 cport)
{
	struct ip_vs_conn_param param;
	struct ip_vs_conn *ct = NULL, *cp = NULL;
	const union nf_inet_addr *vaddr, *daddr, *caddr;
	union nf_inet_addr snet;
	__be16 vport;
	unsigned int flags;

	EnterFunction(12);
	vaddr = &svc->addr;
	vport = svc->port;
	daddr = &iph->saddr;
	caddr = &iph->daddr;

	/* check pre-requisites are satisfied */
	if (svc->fwmark)
		return NULL;
	if (!vport || !dport)
		return NULL;

	/* for persistent service first create connection template */
	if (svc->flags & IP_VS_SVC_F_PERSISTENT) {
		/* apply netmask the same way ingress-side does */
#ifdef CONFIG_IP_VS_IPV6
		if (svc->af == AF_INET6)
			ipv6_addr_prefix(&snet.in6, &caddr->in6,
					 (__force __u32)svc->netmask);
		else
#endif
			snet.ip = caddr->ip & svc->netmask;
		/* fill params and create template if not existent */
		if (ip_vs_conn_fill_param_persist(svc, skb, iph->protocol,
						  &snet, 0, vaddr,
						  vport, &param) < 0)
			return NULL;
		ct = ip_vs_ct_in_get(&param);
		/* check if template exists and points to the same dest */
		if (!ct || !ip_vs_check_template(ct, dest)) {
			ct = ip_vs_conn_new(&param, dest->af, daddr, dport,
					    IP_VS_CONN_F_TEMPLATE, dest, 0);
			if (!ct) {
				kfree(param.pe_data);
				return NULL;
			}
			ct->timeout = svc->timeout;
		} else {
			kfree(param.pe_data);
		}
	}

	/* connection flags */
	flags = ((svc->flags & IP_VS_SVC_F_ONEPACKET) &&
		 iph->protocol == IPPROTO_UDP) ? IP_VS_CONN_F_ONE_PACKET : 0;
	/* create connection */
	ip_vs_conn_fill_param(svc->ipvs, svc->af, iph->protocol,
			      caddr, cport, vaddr, vport, &param);
	cp = ip_vs_conn_new(&param, dest->af, daddr, dport, flags, dest, 0);
	if (!cp) {
		if (ct)
			ip_vs_conn_put(ct);
		return NULL;
	}
	if (ct) {
		ip_vs_control_add(cp, ct);
		ip_vs_conn_put(ct);
	}
	ip_vs_conn_stats(cp, svc);

	/* return connection (will be used to handle outgoing packet) */
	IP_VS_DBG_BUF(6, "New connection RS-initiated:%c c:%s:%u v:%s:%u "
		      "d:%s:%u conn->flags:%X conn->refcnt:%d\n",
		      ip_vs_fwd_tag(cp),
		      IP_VS_DBG_ADDR(cp->af, &cp->caddr), ntohs(cp->cport),
		      IP_VS_DBG_ADDR(cp->af, &cp->vaddr), ntohs(cp->vport),
		      IP_VS_DBG_ADDR(cp->af, &cp->daddr), ntohs(cp->dport),
		      cp->flags, refcount_read(&cp->refcnt));
	LeaveFunction(12);
	return cp;
}