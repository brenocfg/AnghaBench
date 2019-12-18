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
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bind (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg_alen ; 
 int /*<<< orphan*/  cfg_bind_addr ; 
 int /*<<< orphan*/  cfg_connect_timeout_ms ; 
 int /*<<< orphan*/  cfg_family ; 
 scalar_t__ cfg_tcp ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  do_poll (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ interrupted ; 
 scalar_t__ listen (int,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_socket(bool do_tcp)
{
	int fd, val;

	fd = socket(cfg_family, cfg_tcp ? SOCK_STREAM : SOCK_DGRAM, 0);
	if (fd == -1)
		error(1, errno, "socket");

	val = 1 << 21;
	if (setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &val, sizeof(val)))
		error(1, errno, "setsockopt rcvbuf");
	val = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val)))
		error(1, errno, "setsockopt reuseport");

	if (bind(fd, (void *)&cfg_bind_addr, cfg_alen))
		error(1, errno, "bind");

	if (do_tcp) {
		int accept_fd = fd;

		if (listen(accept_fd, 1))
			error(1, errno, "listen");

		do_poll(accept_fd, cfg_connect_timeout_ms);
		if (interrupted)
			exit(0);

		fd = accept(accept_fd, NULL, NULL);
		if (fd == -1)
			error(1, errno, "accept");
		if (close(accept_fd))
			error(1, errno, "close accept fd");
	}

	return fd;
}