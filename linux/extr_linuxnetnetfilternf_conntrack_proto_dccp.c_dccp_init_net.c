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
typedef  int /*<<< orphan*/  u_int16_t ;
struct nf_proto_net {int /*<<< orphan*/  users; } ;
struct nf_dccp_net {int dccp_loose; int* dccp_timeout; struct nf_proto_net pn; } ;
struct net {int dummy; } ;

/* Variables and functions */
 size_t CT_DCCP_CLOSEREQ ; 
 size_t CT_DCCP_CLOSING ; 
 size_t CT_DCCP_NONE ; 
 size_t CT_DCCP_OPEN ; 
 size_t CT_DCCP_PARTOPEN ; 
 size_t CT_DCCP_REQUEST ; 
 size_t CT_DCCP_RESPOND ; 
 size_t CT_DCCP_TIMEWAIT ; 
 int DCCP_MSL ; 
 int HZ ; 
 int dccp_kmemdup_sysctl_table (struct net*,struct nf_proto_net*,struct nf_dccp_net*) ; 
 struct nf_dccp_net* dccp_pernet (struct net*) ; 

__attribute__((used)) static int dccp_init_net(struct net *net, u_int16_t proto)
{
	struct nf_dccp_net *dn = dccp_pernet(net);
	struct nf_proto_net *pn = &dn->pn;

	if (!pn->users) {
		/* default values */
		dn->dccp_loose = 1;
		dn->dccp_timeout[CT_DCCP_REQUEST]	= 2 * DCCP_MSL;
		dn->dccp_timeout[CT_DCCP_RESPOND]	= 4 * DCCP_MSL;
		dn->dccp_timeout[CT_DCCP_PARTOPEN]	= 4 * DCCP_MSL;
		dn->dccp_timeout[CT_DCCP_OPEN]		= 12 * 3600 * HZ;
		dn->dccp_timeout[CT_DCCP_CLOSEREQ]	= 64 * HZ;
		dn->dccp_timeout[CT_DCCP_CLOSING]	= 64 * HZ;
		dn->dccp_timeout[CT_DCCP_TIMEWAIT]	= 2 * DCCP_MSL;

		/* timeouts[0] is unused, make it same as SYN_SENT so
		 * ->timeouts[0] contains 'new' timeout, like udp or icmp.
		 */
		dn->dccp_timeout[CT_DCCP_NONE] = dn->dccp_timeout[CT_DCCP_REQUEST];
	}

	return dccp_kmemdup_sysctl_table(net, pn, dn);
}