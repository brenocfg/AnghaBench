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
typedef  int /*<<< orphan*/  u16 ;
struct tomoyo_inet_addr_info {int is_ipv6; int /*<<< orphan*/  port; int /*<<< orphan*/ * address; } ;
struct tomoyo_addr_info {scalar_t__ protocol; struct tomoyo_inet_addr_info inet; } ;
struct TYPE_2__ {scalar_t__ s6_addr; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; TYPE_1__ sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 unsigned int const SIN6_LEN_RFC2133 ; 
 scalar_t__ SOCK_RAW ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/  const) ; 
 int tomoyo_inet_entry (struct tomoyo_addr_info*) ; 

__attribute__((used)) static int tomoyo_check_inet_address(const struct sockaddr *addr,
				     const unsigned int addr_len,
				     const u16 port,
				     struct tomoyo_addr_info *address)
{
	struct tomoyo_inet_addr_info *i = &address->inet;

	switch (addr->sa_family) {
	case AF_INET6:
		if (addr_len < SIN6_LEN_RFC2133)
			goto skip;
		i->is_ipv6 = true;
		i->address = (__be32 *)
			((struct sockaddr_in6 *) addr)->sin6_addr.s6_addr;
		i->port = ((struct sockaddr_in6 *) addr)->sin6_port;
		break;
	case AF_INET:
		if (addr_len < sizeof(struct sockaddr_in))
			goto skip;
		i->is_ipv6 = false;
		i->address = (__be32 *)
			&((struct sockaddr_in *) addr)->sin_addr;
		i->port = ((struct sockaddr_in *) addr)->sin_port;
		break;
	default:
		goto skip;
	}
	if (address->protocol == SOCK_RAW)
		i->port = htons(port);
	return tomoyo_inet_entry(address);
skip:
	return 0;
}