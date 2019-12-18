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
typedef  int /*<<< orphan*/  uint16_t ;
struct test_params {int recv_socks; scalar_t__ protocol; int /*<<< orphan*/  recv_family; int /*<<< orphan*/  recv_port; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 int /*<<< orphan*/  TCP_FASTOPEN ; 
 scalar_t__ bind (int,struct sockaddr* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct sockaddr* const) ; 
 scalar_t__ listen (int,int) ; 
 struct sockaddr* new_any_sockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sockaddr_size () ; 
 int socket (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_recv_group(const struct test_params p, int fd[], uint16_t mod,
			     void (*attach_bpf)(int, uint16_t))
{
	struct sockaddr * const addr =
		new_any_sockaddr(p.recv_family, p.recv_port);
	int i, opt;

	for (i = 0; i < p.recv_socks; ++i) {
		fd[i] = socket(p.recv_family, p.protocol, 0);
		if (fd[i] < 0)
			error(1, errno, "failed to create recv %d", i);

		opt = 1;
		if (setsockopt(fd[i], SOL_SOCKET, SO_REUSEPORT, &opt,
			       sizeof(opt)))
			error(1, errno, "failed to set SO_REUSEPORT on %d", i);

		if (i == 0)
			attach_bpf(fd[i], mod);

		if (bind(fd[i], addr, sockaddr_size()))
			error(1, errno, "failed to bind recv socket %d", i);

		if (p.protocol == SOCK_STREAM) {
			opt = 4;
			if (setsockopt(fd[i], SOL_TCP, TCP_FASTOPEN, &opt,
				       sizeof(opt)))
				error(1, errno,
				      "failed to set TCP_FASTOPEN on %d", i);
			if (listen(fd[i], p.recv_socks * 10))
				error(1, errno, "failed to listen on socket");
		}
	}
	free(addr);
}