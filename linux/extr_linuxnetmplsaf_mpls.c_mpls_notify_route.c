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
struct nlmsghdr {int dummy; } ;
struct nl_info {unsigned int portid; struct nlmsghdr* nlh; } ;
struct net {int dummy; } ;
struct mpls_route {int dummy; } ;

/* Variables and functions */
 unsigned int MPLS_LABEL_FIRST_UNRESERVED ; 
 unsigned int NLM_F_REPLACE ; 
 int RTM_DELROUTE ; 
 int RTM_NEWROUTE ; 
 int /*<<< orphan*/  rtmsg_lfib (int,unsigned int,struct mpls_route*,struct nlmsghdr*,struct net*,unsigned int,unsigned int) ; 

__attribute__((used)) static void mpls_notify_route(struct net *net, unsigned index,
			      struct mpls_route *old, struct mpls_route *new,
			      const struct nl_info *info)
{
	struct nlmsghdr *nlh = info ? info->nlh : NULL;
	unsigned portid = info ? info->portid : 0;
	int event = new ? RTM_NEWROUTE : RTM_DELROUTE;
	struct mpls_route *rt = new ? new : old;
	unsigned nlm_flags = (old && new) ? NLM_F_REPLACE : 0;
	/* Ignore reserved labels for now */
	if (rt && (index >= MPLS_LABEL_FIRST_UNRESERVED))
		rtmsg_lfib(event, index, rt, nlh, net, portid, nlm_flags);
}