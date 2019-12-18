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
struct msghdr {int msg_iovlen; void* msg_controllen; void* msg_control; int /*<<< orphan*/  msg_namelen; void* msg_name; struct iovec* msg_iov; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct in_pktinfo {int ipi_ifindex; } ;
struct in6_pktinfo {int ipi6_ifindex; } ;
struct cmsghdr {void* cmsg_len; int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  cmsgbuf ;
typedef  void* caddr_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 void* CMSG_LEN (int) ; 
 scalar_t__ EACCES ; 
 int /*<<< orphan*/  IPV6_PKTINFO ; 
 int /*<<< orphan*/  IP_PKTINFO ; 
 int /*<<< orphan*/  SOL_IP ; 
 int /*<<< orphan*/  SOL_IPV6 ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg ; 
 int /*<<< orphan*/  msglen ; 
 int sendmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_broadcast (int) ; 
 scalar_t__ try_broadcast ; 

__attribute__((used)) static int send_msg_cmsg(int sd, void *addr, socklen_t alen,
			 int ifindex, int version)
{
	unsigned char cmsgbuf[64];
	struct iovec iov[2];
	struct cmsghdr *cm;
	struct msghdr m;
	int err;

	iov[0].iov_base = msg;
	iov[0].iov_len = msglen;
	m.msg_iov = iov;
	m.msg_iovlen = 1;
	m.msg_name = (caddr_t)addr;
	m.msg_namelen = alen;

	memset(cmsgbuf, 0, sizeof(cmsgbuf));
	cm = (struct cmsghdr *)cmsgbuf;
	m.msg_control = (caddr_t)cm;

	if (version == AF_INET) {
		struct in_pktinfo *pi;

		cm->cmsg_level = SOL_IP;
		cm->cmsg_type = IP_PKTINFO;
		cm->cmsg_len = CMSG_LEN(sizeof(struct in_pktinfo));
		pi = (struct in_pktinfo *)(CMSG_DATA(cm));
		pi->ipi_ifindex = ifindex;

		m.msg_controllen = cm->cmsg_len;

	} else if (version == AF_INET6) {
		struct in6_pktinfo *pi6;

		cm->cmsg_level = SOL_IPV6;
		cm->cmsg_type = IPV6_PKTINFO;
		cm->cmsg_len = CMSG_LEN(sizeof(struct in6_pktinfo));

		pi6 = (struct in6_pktinfo *)(CMSG_DATA(cm));
		pi6->ipi6_ifindex = ifindex;

		m.msg_controllen = cm->cmsg_len;
	}

again:
	err = sendmsg(sd, &m, 0);
	if (err < 0) {
		if (errno == EACCES && try_broadcast) {
			try_broadcast = 0;
			if (!set_broadcast(sd))
				goto again;
			errno = EACCES;
		}

		log_err_errno("sendmsg failed");
		return 1;
	}

	return 0;
}