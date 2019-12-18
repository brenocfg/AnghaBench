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

/* Variables and functions */
 int IPPROTO_RAW ; 
 int PF_PACKET ; 
 int SOCK_RAW ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_RCVLOWAT ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 scalar_t__ bind (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg_alen ; 
 int /*<<< orphan*/  cfg_dst_addr ; 
 int do_accept (int) ; 
 int /*<<< orphan*/  do_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ listen (int,int) ; 
 int socket (int,int,int) ; 

__attribute__((used)) static int do_setup_rx(int domain, int type, int protocol)
{
	int fd;

	/* If tx over PF_PACKET, rx over PF_INET(6)/SOCK_RAW,
	 * to recv the only copy of the packet, not a clone
	 */
	if (domain == PF_PACKET)
		error(1, 0, "Use PF_INET/SOCK_RAW to read");

	if (type == SOCK_RAW && protocol == IPPROTO_RAW)
		error(1, 0, "IPPROTO_RAW: not supported on Rx");

	fd = socket(domain, type, protocol);
	if (fd == -1)
		error(1, errno, "socket r");

	do_setsockopt(fd, SOL_SOCKET, SO_RCVBUF, 1 << 21);
	do_setsockopt(fd, SOL_SOCKET, SO_RCVLOWAT, 1 << 16);
	do_setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, 1);

	if (bind(fd, (void *) &cfg_dst_addr, cfg_alen))
		error(1, errno, "bind");

	if (type == SOCK_STREAM) {
		if (listen(fd, 1))
			error(1, errno, "listen");
		fd = do_accept(fd);
	}

	return fd;
}