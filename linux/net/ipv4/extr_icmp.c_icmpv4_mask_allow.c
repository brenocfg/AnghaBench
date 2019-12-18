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
struct TYPE_2__ {int sysctl_icmp_ratemask; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int ICMP_DEST_UNREACH ; 
 int ICMP_FRAG_NEEDED ; 
 int NR_ICMP_TYPES ; 

__attribute__((used)) static bool icmpv4_mask_allow(struct net *net, int type, int code)
{
	if (type > NR_ICMP_TYPES)
		return true;

	/* Don't limit PMTU discovery. */
	if (type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED)
		return true;

	/* Limit if icmp type is enabled in ratemask. */
	if (!((1 << type) & net->ipv4.sysctl_icmp_ratemask))
		return true;

	return false;
}