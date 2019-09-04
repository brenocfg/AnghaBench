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
struct rtnexthop {int dummy; } ;
struct rtmsg {int dummy; } ;
struct rta_mfc_stats {int dummy; } ;

/* Variables and functions */
 int NLA_ALIGN (int) ; 
 size_t NLMSG_ALIGN (int) ; 
 size_t nla_total_size (int) ; 
 size_t nla_total_size_64bit (int) ; 

__attribute__((used)) static size_t mroute_msgsize(bool unresolved, int maxvif)
{
	size_t len =
		NLMSG_ALIGN(sizeof(struct rtmsg))
		+ nla_total_size(4)	/* RTA_TABLE */
		+ nla_total_size(4)	/* RTA_SRC */
		+ nla_total_size(4)	/* RTA_DST */
		;

	if (!unresolved)
		len = len
		      + nla_total_size(4)	/* RTA_IIF */
		      + nla_total_size(0)	/* RTA_MULTIPATH */
		      + maxvif * NLA_ALIGN(sizeof(struct rtnexthop))
						/* RTA_MFC_STATS */
		      + nla_total_size_64bit(sizeof(struct rta_mfc_stats))
		;

	return len;
}