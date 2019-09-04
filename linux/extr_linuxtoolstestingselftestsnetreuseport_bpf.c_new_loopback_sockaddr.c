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
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 struct sockaddr* new_any_sockaddr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sockaddr *new_loopback_sockaddr(int family, uint16_t port)
{
	struct sockaddr *addr = new_any_sockaddr(family, port);
	struct sockaddr_in *addr4;
	struct sockaddr_in6 *addr6;

	switch (family) {
	case AF_INET:
		addr4 = (struct sockaddr_in *)addr;
		addr4->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		break;
	case AF_INET6:
		addr6 = (struct sockaddr_in6 *)addr;
		addr6->sin6_addr = in6addr_loopback;
		break;
	default:
		error(1, 0, "Unsupported family %d", family);
	}
	return addr;
}