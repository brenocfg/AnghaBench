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
struct sockaddr_nl {int /*<<< orphan*/  nl_family; } ;
struct msghdr {int msg_namelen; int msg_iovlen; struct iovec* msg_iov; struct sockaddr_nl* msg_name; } ;
struct iovec {void* iov_base; size_t iov_len; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  nladdr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETLINK ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ recvmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t recv_resp(int fd, void *buf, size_t len)
{
	struct sockaddr_nl nladdr = {
		.nl_family = AF_NETLINK,
	};
	struct iovec iov = {
		.iov_base = buf,
		.iov_len = len,
	};
	struct msghdr msg = {
		.msg_name = &nladdr,
		.msg_namelen = sizeof(nladdr),
		.msg_iov = &iov,
		.msg_iovlen = 1,
	};
	ssize_t ret;

	do {
		ret = recvmsg(fd, &msg, 0);
	} while (ret < 0 && errno == EINTR);

	if (ret < 0) {
		perror("recvmsg");
		exit(EXIT_FAILURE);
	}

	return ret;
}