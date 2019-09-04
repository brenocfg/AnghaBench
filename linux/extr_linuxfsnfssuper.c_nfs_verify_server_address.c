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
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  MOUNT ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_addr_any (struct in6_addr*) ; 

__attribute__((used)) static int nfs_verify_server_address(struct sockaddr *addr)
{
	switch (addr->sa_family) {
	case AF_INET: {
		struct sockaddr_in *sa = (struct sockaddr_in *)addr;
		return sa->sin_addr.s_addr != htonl(INADDR_ANY);
	}
	case AF_INET6: {
		struct in6_addr *sa = &((struct sockaddr_in6 *)addr)->sin6_addr;
		return !ipv6_addr_any(sa);
	}
	}

	dfprintk(MOUNT, "NFS: Invalid IP address specified\n");
	return 0;
}