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
struct test_params {int /*<<< orphan*/  protocol; int /*<<< orphan*/  recv_family; int /*<<< orphan*/  recv_port; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 scalar_t__ EADDRINUSE ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 int /*<<< orphan*/  attach_ebpf (int,int) ; 
 scalar_t__ bind (int,struct sockaddr* const,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (int,scalar_t__,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct sockaddr* const) ; 
 struct sockaddr* new_any_sockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sockaddr_size () ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void test_extra_filter(const struct test_params p)
{
	struct sockaddr * const addr =
		new_any_sockaddr(p.recv_family, p.recv_port);
	int fd1, fd2, opt;

	fprintf(stderr, "Testing too many filters...\n");
	fd1 = socket(p.recv_family, p.protocol, 0);
	if (fd1 < 0)
		error(1, errno, "failed to create socket 1");
	fd2 = socket(p.recv_family, p.protocol, 0);
	if (fd2 < 0)
		error(1, errno, "failed to create socket 2");

	opt = 1;
	if (setsockopt(fd1, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
		error(1, errno, "failed to set SO_REUSEPORT on socket 1");
	if (setsockopt(fd2, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
		error(1, errno, "failed to set SO_REUSEPORT on socket 2");

	attach_ebpf(fd1, 10);
	attach_ebpf(fd2, 10);

	if (bind(fd1, addr, sockaddr_size()))
		error(1, errno, "failed to bind recv socket 1");

	if (!bind(fd2, addr, sockaddr_size()) && errno != EADDRINUSE)
		error(1, errno, "bind socket 2 should fail with EADDRINUSE");

	free(addr);
}