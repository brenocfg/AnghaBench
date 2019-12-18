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
typedef  int /*<<< orphan*/  test_family ;
struct TYPE_2__ {int fd; } ;
struct epoll_event {TYPE_1__ data; int /*<<< orphan*/  events; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int AF_INET ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_DOMAIN ; 
 int /*<<< orphan*/  close (int) ; 
 int epoll_create (int) ; 
 scalar_t__ epoll_ctl (int,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int receive_once (int,int) ; 
 int /*<<< orphan*/  send_from_v4 (int) ; 

__attribute__((used)) static void test(int *rcv_fds, int count, int proto)
{
	struct epoll_event ev;
	int epfd, i, test_fd;
	int test_family;
	socklen_t len;

	epfd = epoll_create(1);
	if (epfd < 0)
		error(1, errno, "failed to create epoll");

	ev.events = EPOLLIN;
	for (i = 0; i < count; ++i) {
		ev.data.fd = rcv_fds[i];
		if (epoll_ctl(epfd, EPOLL_CTL_ADD, rcv_fds[i], &ev))
			error(1, errno, "failed to register sock epoll");
	}

	send_from_v4(proto);

	test_fd = receive_once(epfd, proto);
	len = sizeof(test_family);
	if (getsockopt(test_fd, SOL_SOCKET, SO_DOMAIN, &test_family, &len))
		error(1, errno, "failed to read socket domain");
	if (test_family != AF_INET)
		error(1, 0, "expected to receive on v4 socket but got v6 (%d)",
		      test_family);

	close(epfd);
}