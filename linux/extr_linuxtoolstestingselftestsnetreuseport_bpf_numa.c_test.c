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
 int /*<<< orphan*/  attach_bpf (int) ; 
 int /*<<< orphan*/  build_rcv_group (int*,int,int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int epoll_create (int) ; 
 scalar_t__ epoll_ctl (int,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  receive_on_node (int*,int,int,int,int) ; 
 int /*<<< orphan*/  send_from_node (int,int,int) ; 

__attribute__((used)) static void test(int *rcv_fd, int len, int family, int proto)
{
	struct epoll_event ev;
	int epfd, node;

	build_rcv_group(rcv_fd, len, family, proto);
	attach_bpf(rcv_fd[0]);

	epfd = epoll_create(1);
	if (epfd < 0)
		error(1, errno, "failed to create epoll");
	for (node = 0; node < len; ++node) {
		ev.events = EPOLLIN;
		ev.data.fd = rcv_fd[node];
		if (epoll_ctl(epfd, EPOLL_CTL_ADD, rcv_fd[node], &ev))
			error(1, errno, "failed to register sock epoll");
	}

	/* Forward iterate */
	for (node = 0; node < len; ++node) {
		send_from_node(node, family, proto);
		receive_on_node(rcv_fd, len, epfd, node, proto);
	}

	/* Reverse iterate */
	for (node = len - 1; node >= 0; --node) {
		send_from_node(node, family, proto);
		receive_on_node(rcv_fd, len, epfd, node, proto);
	}

	close(epfd);
	for (node = 0; node < len; ++node)
		close(rcv_fd[node]);
}