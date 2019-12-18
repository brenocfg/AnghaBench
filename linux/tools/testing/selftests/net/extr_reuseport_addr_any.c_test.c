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
struct TYPE_2__ {int fd; } ;
struct epoll_event {TYPE_1__ data; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  close (int) ; 
 int connect_and_send (int,int) ; 
 int epoll_create (int) ; 
 scalar_t__ epoll_ctl (int,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int receive_once (int,int) ; 

__attribute__((used)) static void test(int *rcv_fds, int count, int family, int proto, int fd)
{
	struct epoll_event ev;
	int epfd, i, send_fd, recv_fd;

	epfd = epoll_create(1);
	if (epfd < 0)
		error(1, errno, "failed to create epoll");

	ev.events = EPOLLIN;
	for (i = 0; i < count; ++i) {
		ev.data.fd = rcv_fds[i];
		if (epoll_ctl(epfd, EPOLL_CTL_ADD, rcv_fds[i], &ev))
			error(1, errno, "failed to register sock epoll");
	}

	send_fd = connect_and_send(family, proto);

	recv_fd = receive_once(epfd, proto);
	if (recv_fd != fd)
		error(1, 0, "received on an unexpected socket");

	close(send_fd);
	close(epfd);
}