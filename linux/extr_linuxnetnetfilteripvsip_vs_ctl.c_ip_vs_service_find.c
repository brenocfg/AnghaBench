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
struct netns_ipvs {int /*<<< orphan*/  nullsvc_counter; int /*<<< orphan*/  net; int /*<<< orphan*/  ftpsvc_counter; } ;
struct ip_vs_service {int dummy; } ;
typedef  scalar_t__ __u32 ;
typedef  scalar_t__ __u16 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 scalar_t__ FTPDATA ; 
 scalar_t__ FTPPORT ; 
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  IP_VS_DBG_ADDR (int,union nf_inet_addr const*) ; 
 int /*<<< orphan*/  IP_VS_DBG_BUF (int,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 struct ip_vs_service* __ip_vs_service_find (struct netns_ipvs*,int,scalar_t__,union nf_inet_addr const*,scalar_t__) ; 
 struct ip_vs_service* __ip_vs_svc_fwm_find (struct netns_ipvs*,int,scalar_t__) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ inet_prot_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_proto_name (scalar_t__) ; 
 scalar_t__ ntohs (scalar_t__) ; 

struct ip_vs_service *
ip_vs_service_find(struct netns_ipvs *ipvs, int af, __u32 fwmark, __u16 protocol,
		   const union nf_inet_addr *vaddr, __be16 vport)
{
	struct ip_vs_service *svc;

	/*
	 *	Check the table hashed by fwmark first
	 */
	if (fwmark) {
		svc = __ip_vs_svc_fwm_find(ipvs, af, fwmark);
		if (svc)
			goto out;
	}

	/*
	 *	Check the table hashed by <protocol,addr,port>
	 *	for "full" addressed entries
	 */
	svc = __ip_vs_service_find(ipvs, af, protocol, vaddr, vport);

	if (!svc && protocol == IPPROTO_TCP &&
	    atomic_read(&ipvs->ftpsvc_counter) &&
	    (vport == FTPDATA || ntohs(vport) >= inet_prot_sock(ipvs->net))) {
		/*
		 * Check if ftp service entry exists, the packet
		 * might belong to FTP data connections.
		 */
		svc = __ip_vs_service_find(ipvs, af, protocol, vaddr, FTPPORT);
	}

	if (svc == NULL
	    && atomic_read(&ipvs->nullsvc_counter)) {
		/*
		 * Check if the catch-all port (port zero) exists
		 */
		svc = __ip_vs_service_find(ipvs, af, protocol, vaddr, 0);
	}

  out:
	IP_VS_DBG_BUF(9, "lookup service: fwm %u %s %s:%u %s\n",
		      fwmark, ip_vs_proto_name(protocol),
		      IP_VS_DBG_ADDR(af, vaddr), ntohs(vport),
		      svc ? "hit" : "not hit");

	return svc;
}