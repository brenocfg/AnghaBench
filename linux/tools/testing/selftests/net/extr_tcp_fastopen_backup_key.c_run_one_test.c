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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int N_LISTEN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_rcv_fd (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect_and_send (int,int /*<<< orphan*/ ) ; 
 scalar_t__ do_rotate ; 
 int epoll_create (int) ; 
 scalar_t__ epoll_ctl (int,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int epoll_wait (int,struct epoll_event*,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_listen_fd (int) ; 
 int* rcv_fds ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rotate_key (int) ; 

__attribute__((used)) static void run_one_test(int family)
{
	struct epoll_event ev;
	int i, send_fd;
	int n_loops = 10000;
	int rotate_key_fd = 0;
	int key_rotate_interval = 50;
	int fd, epfd;
	char buf[1];

	build_rcv_fd(family, SOCK_STREAM, rcv_fds);
	epfd = epoll_create(1);
	if (epfd < 0)
		error(1, errno, "failed to create epoll");
	ev.events = EPOLLIN;
	for (i = 0; i < N_LISTEN; i++) {
		ev.data.fd = rcv_fds[i];
		if (epoll_ctl(epfd, EPOLL_CTL_ADD, rcv_fds[i], &ev))
			error(1, errno, "failed to register sock epoll");
	}
	while (n_loops--) {
		send_fd = connect_and_send(family, SOCK_STREAM);
		if (do_rotate && ((n_loops % key_rotate_interval) == 0)) {
			rotate_key(rcv_fds[rotate_key_fd]);
			if (++rotate_key_fd >= N_LISTEN)
				rotate_key_fd = 0;
		}
		while (1) {
			i = epoll_wait(epfd, &ev, 1, -1);
			if (i < 0)
				error(1, errno, "epoll_wait failed");
			if (is_listen_fd(ev.data.fd)) {
				fd = accept(ev.data.fd, NULL, NULL);
				if (fd < 0)
					error(1, errno, "failed to accept");
				ev.data.fd = fd;
				if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev))
					error(1, errno, "failed epoll add");
				continue;
			}
			i = recv(ev.data.fd, buf, sizeof(buf), 0);
			if (i != 1)
				error(1, errno, "failed recv data");
			if (epoll_ctl(epfd, EPOLL_CTL_DEL, ev.data.fd, NULL))
				error(1, errno, "failed epoll del");
			close(ev.data.fd);
			break;
		}
		close(send_fd);
	}
	for (i = 0; i < N_LISTEN; i++)
		close(rcv_fds[i]);
}