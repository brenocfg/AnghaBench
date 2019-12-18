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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct TCP_Server_Info {int /*<<< orphan*/  srcaddr; int /*<<< orphan*/  dstaddr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcip_matches (struct sockaddr*,struct sockaddr*) ; 

__attribute__((used)) static bool
match_address(struct TCP_Server_Info *server, struct sockaddr *addr,
	      struct sockaddr *srcaddr)
{
	switch (addr->sa_family) {
	case AF_INET: {
		struct sockaddr_in *addr4 = (struct sockaddr_in *)addr;
		struct sockaddr_in *srv_addr4 =
					(struct sockaddr_in *)&server->dstaddr;

		if (addr4->sin_addr.s_addr != srv_addr4->sin_addr.s_addr)
			return false;
		break;
	}
	case AF_INET6: {
		struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)addr;
		struct sockaddr_in6 *srv_addr6 =
					(struct sockaddr_in6 *)&server->dstaddr;

		if (!ipv6_addr_equal(&addr6->sin6_addr,
				     &srv_addr6->sin6_addr))
			return false;
		if (addr6->sin6_scope_id != srv_addr6->sin6_scope_id)
			return false;
		break;
	}
	default:
		WARN_ON(1);
		return false; /* don't expect to be here */
	}

	if (!srcip_matches(srcaddr, (struct sockaddr *)&server->srcaddr))
		return false;

	return true;
}