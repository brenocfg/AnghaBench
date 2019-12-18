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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int sin6_family; void* sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_family; void* sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  PORT ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_any ; 
 scalar_t__ listen (int,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_rcv_fd(int family, int proto, int *rcv_fds, int count)
{
	struct sockaddr_storage addr;
	struct sockaddr_in  *addr4;
	struct sockaddr_in6 *addr6;
	int opt, i;

	switch (family) {
	case AF_INET:
		addr4 = (struct sockaddr_in *)&addr;
		addr4->sin_family = AF_INET;
		addr4->sin_addr.s_addr = htonl(INADDR_ANY);
		addr4->sin_port = htons(PORT);
		break;
	case AF_INET6:
		addr6 = (struct sockaddr_in6 *)&addr;
		addr6->sin6_family = AF_INET6;
		addr6->sin6_addr = in6addr_any;
		addr6->sin6_port = htons(PORT);
		break;
	default:
		error(1, 0, "Unsupported family %d", family);
	}

	for (i = 0; i < count; ++i) {
		rcv_fds[i] = socket(family, proto, 0);
		if (rcv_fds[i] < 0)
			error(1, errno, "failed to create receive socket");

		opt = 1;
		if (setsockopt(rcv_fds[i], SOL_SOCKET, SO_REUSEPORT, &opt,
			       sizeof(opt)))
			error(1, errno, "failed to set SO_REUSEPORT");

		if (bind(rcv_fds[i], (struct sockaddr *)&addr, sizeof(addr)))
			error(1, errno, "failed to bind receive socket");

		if (proto == SOCK_STREAM && listen(rcv_fds[i], 10))
			error(1, errno, "failed to listen on receive port");
	}
}