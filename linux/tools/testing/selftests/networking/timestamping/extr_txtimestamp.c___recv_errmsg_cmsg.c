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
struct sock_extended_err {scalar_t__ ee_errno; scalar_t__ ee_origin; int /*<<< orphan*/  ee_data; int /*<<< orphan*/  ee_info; } ;
struct scm_timestamping {int dummy; } ;
struct msghdr {int dummy; } ;
struct in_pktinfo {int /*<<< orphan*/  ipi_addr; int /*<<< orphan*/  ipi_spec_dst; int /*<<< orphan*/  ipi_ifindex; } ;
struct in6_pktinfo {int /*<<< orphan*/  ipi6_addr; int /*<<< orphan*/  ipi6_ifindex; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; scalar_t__ cmsg_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 scalar_t__ ENOMSG ; 
 scalar_t__ IPV6_PKTINFO ; 
 scalar_t__ IPV6_RECVERR ; 
 scalar_t__ IP_PKTINFO ; 
 scalar_t__ IP_RECVERR ; 
 scalar_t__ PACKET_TX_TIMESTAMP ; 
 scalar_t__ SCM_TIMESTAMPING ; 
 scalar_t__ SOL_IP ; 
 scalar_t__ SOL_IPV6 ; 
 scalar_t__ SOL_PACKET ; 
 scalar_t__ SOL_SOCKET ; 
 scalar_t__ SO_EE_ORIGIN_TIMESTAMPING ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  print_pktinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_timestamp (struct scm_timestamping*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void __recv_errmsg_cmsg(struct msghdr *msg, int payload_len)
{
	struct sock_extended_err *serr = NULL;
	struct scm_timestamping *tss = NULL;
	struct cmsghdr *cm;
	int batch = 0;

	for (cm = CMSG_FIRSTHDR(msg);
	     cm && cm->cmsg_len;
	     cm = CMSG_NXTHDR(msg, cm)) {
		if (cm->cmsg_level == SOL_SOCKET &&
		    cm->cmsg_type == SCM_TIMESTAMPING) {
			tss = (void *) CMSG_DATA(cm);
		} else if ((cm->cmsg_level == SOL_IP &&
			    cm->cmsg_type == IP_RECVERR) ||
			   (cm->cmsg_level == SOL_IPV6 &&
			    cm->cmsg_type == IPV6_RECVERR) ||
			   (cm->cmsg_level == SOL_PACKET &&
			    cm->cmsg_type == PACKET_TX_TIMESTAMP)) {
			serr = (void *) CMSG_DATA(cm);
			if (serr->ee_errno != ENOMSG ||
			    serr->ee_origin != SO_EE_ORIGIN_TIMESTAMPING) {
				fprintf(stderr, "unknown ip error %d %d\n",
						serr->ee_errno,
						serr->ee_origin);
				serr = NULL;
			}
		} else if (cm->cmsg_level == SOL_IP &&
			   cm->cmsg_type == IP_PKTINFO) {
			struct in_pktinfo *info = (void *) CMSG_DATA(cm);
			print_pktinfo(AF_INET, info->ipi_ifindex,
				      &info->ipi_spec_dst, &info->ipi_addr);
		} else if (cm->cmsg_level == SOL_IPV6 &&
			   cm->cmsg_type == IPV6_PKTINFO) {
			struct in6_pktinfo *info6 = (void *) CMSG_DATA(cm);
			print_pktinfo(AF_INET6, info6->ipi6_ifindex,
				      NULL, &info6->ipi6_addr);
		} else
			fprintf(stderr, "unknown cmsg %d,%d\n",
					cm->cmsg_level, cm->cmsg_type);

		if (serr && tss) {
			print_timestamp(tss, serr->ee_info, serr->ee_data,
					payload_len);
			serr = NULL;
			tss = NULL;
			batch++;
		}
	}

	if (batch > 1)
		fprintf(stderr, "batched %d timestamps\n", batch);
}