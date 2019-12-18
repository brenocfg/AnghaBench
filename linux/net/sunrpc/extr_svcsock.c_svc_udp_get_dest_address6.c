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
struct svc_rqst {int dummy; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct in6_pktinfo {int /*<<< orphan*/  ipi6_ifindex; int /*<<< orphan*/  ipi6_addr; } ;
struct cmsghdr {scalar_t__ cmsg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 struct in6_pktinfo* CMSG_DATA (struct cmsghdr*) ; 
 scalar_t__ IPV6_PKTINFO ; 
 struct sockaddr_in6* svc_daddr_in6 (struct svc_rqst*) ; 

__attribute__((used)) static int svc_udp_get_dest_address6(struct svc_rqst *rqstp,
				     struct cmsghdr *cmh)
{
	struct in6_pktinfo *pki = CMSG_DATA(cmh);
	struct sockaddr_in6 *daddr = svc_daddr_in6(rqstp);

	if (cmh->cmsg_type != IPV6_PKTINFO)
		return 0;

	daddr->sin6_family = AF_INET6;
	daddr->sin6_addr = pki->ipi6_addr;
	daddr->sin6_scope_id = pki->ipi6_ifindex;
	return 1;
}