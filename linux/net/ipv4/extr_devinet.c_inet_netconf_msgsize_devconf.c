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
struct netconfmsg {int dummy; } ;

/* Variables and functions */
 int NETCONFA_ALL ; 
 int NETCONFA_BC_FORWARDING ; 
 int NETCONFA_FORWARDING ; 
 int NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN ; 
 int NETCONFA_MC_FORWARDING ; 
 int NETCONFA_PROXY_NEIGH ; 
 int NETCONFA_RP_FILTER ; 
 int NLMSG_ALIGN (int) ; 
 int nla_total_size (int) ; 

__attribute__((used)) static int inet_netconf_msgsize_devconf(int type)
{
	int size = NLMSG_ALIGN(sizeof(struct netconfmsg))
		   + nla_total_size(4);	/* NETCONFA_IFINDEX */
	bool all = false;

	if (type == NETCONFA_ALL)
		all = true;

	if (all || type == NETCONFA_FORWARDING)
		size += nla_total_size(4);
	if (all || type == NETCONFA_RP_FILTER)
		size += nla_total_size(4);
	if (all || type == NETCONFA_MC_FORWARDING)
		size += nla_total_size(4);
	if (all || type == NETCONFA_BC_FORWARDING)
		size += nla_total_size(4);
	if (all || type == NETCONFA_PROXY_NEIGH)
		size += nla_total_size(4);
	if (all || type == NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN)
		size += nla_total_size(4);

	return size;
}