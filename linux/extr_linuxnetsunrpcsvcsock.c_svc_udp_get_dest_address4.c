#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct in_pktinfo {TYPE_2__ ipi_spec_dst; } ;
struct cmsghdr {scalar_t__ cmsg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 struct in_pktinfo* CMSG_DATA (struct cmsghdr*) ; 
 scalar_t__ IP_PKTINFO ; 
 struct sockaddr_in* svc_daddr_in (struct svc_rqst*) ; 

__attribute__((used)) static int svc_udp_get_dest_address4(struct svc_rqst *rqstp,
				     struct cmsghdr *cmh)
{
	struct in_pktinfo *pki = CMSG_DATA(cmh);
	struct sockaddr_in *daddr = svc_daddr_in(rqstp);

	if (cmh->cmsg_type != IP_PKTINFO)
		return 0;

	daddr->sin_family = AF_INET;
	daddr->sin_addr.s_addr = pki->ipi_spec_dst.s_addr;
	return 1;
}