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
typedef  int /*<<< orphan*/  uint32_t ;
struct sockaddr_in6 {int sin6_family; void* sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_family; void* sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  member_0; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  qlen ;
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  addr6 ;
typedef  int /*<<< orphan*/  addr4 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int N_LISTEN ; 
 int /*<<< orphan*/  PORT ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 int /*<<< orphan*/  TCP_FASTOPEN ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_any ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  set_keys (int,int /*<<< orphan*/ *) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_rcv_fd(int family, int proto, int *rcv_fds)
{
	struct sockaddr_in  addr4 = {0};
	struct sockaddr_in6 addr6 = {0};
	struct sockaddr *addr;
	int opt = 1, i, sz;
	int qlen = 100;
	uint32_t keys[8];

	switch (family) {
	case AF_INET:
		addr4.sin_family = family;
		addr4.sin_addr.s_addr = htonl(INADDR_ANY);
		addr4.sin_port = htons(PORT);
		sz = sizeof(addr4);
		addr = (struct sockaddr *)&addr4;
		break;
	case AF_INET6:
		addr6.sin6_family = AF_INET6;
		addr6.sin6_addr = in6addr_any;
		addr6.sin6_port = htons(PORT);
		sz = sizeof(addr6);
		addr = (struct sockaddr *)&addr6;
		break;
	default:
		error(1, 0, "Unsupported family %d", family);
		/* clang does not recognize error() above as terminating
		 * the program, so it complains that saddr, sz are
		 * not initialized when this code path is taken. Silence it.
		 */
		return;
	}
	for (i = 0; i < ARRAY_SIZE(keys); i++)
		keys[i] = rand();
	for (i = 0; i < N_LISTEN; i++) {
		rcv_fds[i] = socket(family, proto, 0);
		if (rcv_fds[i] < 0)
			error(1, errno, "failed to create receive socket");
		if (setsockopt(rcv_fds[i], SOL_SOCKET, SO_REUSEPORT, &opt,
			       sizeof(opt)))
			error(1, errno, "failed to set SO_REUSEPORT");
		if (bind(rcv_fds[i], addr, sz))
			error(1, errno, "failed to bind receive socket");
		if (setsockopt(rcv_fds[i], SOL_TCP, TCP_FASTOPEN, &qlen,
			       sizeof(qlen)))
			error(1, errno, "failed to set TCP_FASTOPEN");
		set_keys(rcv_fds[i], keys);
		if (proto == SOCK_STREAM && listen(rcv_fds[i], 10))
			error(1, errno, "failed to listen on receive port");
	}
}