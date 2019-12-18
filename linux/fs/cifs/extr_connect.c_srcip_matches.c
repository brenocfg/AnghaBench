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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNSPEC 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ipv6_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
srcip_matches(struct sockaddr *srcaddr, struct sockaddr *rhs)
{
	switch (srcaddr->sa_family) {
	case AF_UNSPEC:
		return (rhs->sa_family == AF_UNSPEC);
	case AF_INET: {
		struct sockaddr_in *saddr4 = (struct sockaddr_in *)srcaddr;
		struct sockaddr_in *vaddr4 = (struct sockaddr_in *)rhs;
		return (saddr4->sin_addr.s_addr == vaddr4->sin_addr.s_addr);
	}
	case AF_INET6: {
		struct sockaddr_in6 *saddr6 = (struct sockaddr_in6 *)srcaddr;
		struct sockaddr_in6 *vaddr6 = (struct sockaddr_in6 *)rhs;
		return ipv6_addr_equal(&saddr6->sin6_addr, &vaddr6->sin6_addr);
	}
	default:
		WARN_ON(1);
		return false; /* don't expect to be here */
	}
}