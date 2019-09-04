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
struct epoll_event {TYPE_1__ data; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int SOCK_STREAM ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int epoll_wait (int,struct epoll_event*,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
void receive_on_node(int *rcv_fd, int len, int epfd, int node_id, int proto)
{
	struct epoll_event ev;
	int i, fd;
	char buf[8];

	i = epoll_wait(epfd, &ev, 1, -1);
	if (i < 0)
		error(1, errno, "epoll_wait failed");

	if (proto == SOCK_STREAM) {
		fd = accept(ev.data.fd, NULL, NULL);
		if (fd < 0)
			error(1, errno, "failed to accept");
		i = recv(fd, buf, sizeof(buf), 0);
		close(fd);
	} else {
		i = recv(ev.data.fd, buf, sizeof(buf), 0);
	}

	if (i < 0)
		error(1, errno, "failed to recv");

	for (i = 0; i < len; ++i)
		if (ev.data.fd == rcv_fd[i])
			break;
	if (i == len)
		error(1, 0, "failed to find socket");
	fprintf(stderr, "send node %d, receive socket %d\n", node_id, i);
	if (node_id != i)
		error(1, 0, "node id/receive socket mismatch");
}