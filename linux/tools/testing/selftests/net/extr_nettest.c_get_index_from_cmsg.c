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
struct msghdr {scalar_t__ msg_controllen; } ;
struct in_pktinfo {int ipi_ifindex; int /*<<< orphan*/  ipi_addr; } ;
struct in6_pktinfo {int ipi6_ifindex; int /*<<< orphan*/  ipi6_addr; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 scalar_t__ CMSG_FIRSTHDR (struct msghdr*) ; 
 scalar_t__ CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 scalar_t__ IPV6_PKTINFO ; 
 scalar_t__ IP_PKTINFO ; 
 scalar_t__ SOL_IP ; 
 scalar_t__ SOL_IPV6 ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  log_msg (char*,int,char*) ; 

__attribute__((used)) static int get_index_from_cmsg(struct msghdr *m)
{
	struct cmsghdr *cm;
	int ifindex = 0;
	char buf[64];

	for (cm = (struct cmsghdr *)CMSG_FIRSTHDR(m);
	     m->msg_controllen != 0 && cm;
	     cm = (struct cmsghdr *)CMSG_NXTHDR(m, cm)) {

		if (cm->cmsg_level == SOL_IP &&
		    cm->cmsg_type == IP_PKTINFO) {
			struct in_pktinfo *pi;

			pi = (struct in_pktinfo *)(CMSG_DATA(cm));
			inet_ntop(AF_INET, &pi->ipi_addr, buf, sizeof(buf));
			ifindex = pi->ipi_ifindex;
		} else if (cm->cmsg_level == SOL_IPV6 &&
			   cm->cmsg_type == IPV6_PKTINFO) {
			struct in6_pktinfo *pi6;

			pi6 = (struct in6_pktinfo *)(CMSG_DATA(cm));
			inet_ntop(AF_INET6, &pi6->ipi6_addr, buf, sizeof(buf));
			ifindex = pi6->ipi6_ifindex;
		}
	}

	if (ifindex) {
		log_msg("    pktinfo: ifindex %d dest addr %s\n",
			ifindex, buf);
	}
	return ifindex;
}