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
 int PF_PACKET ; 
 int PF_RDS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  SO_ZEROCOPY ; 
 scalar_t__ bind (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg_alen ; 
 int /*<<< orphan*/  cfg_dst_addr ; 
 int /*<<< orphan*/  cfg_src_addr ; 
 scalar_t__ cfg_zerocopy ; 
 scalar_t__ connect (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int socket (int,int,int) ; 

__attribute__((used)) static int do_setup_tx(int domain, int type, int protocol)
{
	int fd;

	fd = socket(domain, type, protocol);
	if (fd == -1)
		error(1, errno, "socket t");

	do_setsockopt(fd, SOL_SOCKET, SO_SNDBUF, 1 << 21);
	if (cfg_zerocopy)
		do_setsockopt(fd, SOL_SOCKET, SO_ZEROCOPY, 1);

	if (domain != PF_PACKET && domain != PF_RDS)
		if (connect(fd, (void *) &cfg_dst_addr, cfg_alen))
			error(1, errno, "connect");

	if (domain == PF_RDS) {
		if (bind(fd, (void *) &cfg_src_addr, cfg_alen))
			error(1, errno, "bind");
	}

	return fd;
}