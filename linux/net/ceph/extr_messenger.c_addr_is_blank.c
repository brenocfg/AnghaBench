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
struct sockaddr_storage {int ss_family; } ;
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {struct in_addr sin_addr; } ;
struct ceph_entity_addr {struct sockaddr_storage in_addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int ipv6_addr_any (struct in6_addr*) ; 

__attribute__((used)) static bool addr_is_blank(struct ceph_entity_addr *addr)
{
	struct sockaddr_storage ss = addr->in_addr; /* align */
	struct in_addr *addr4 = &((struct sockaddr_in *)&ss)->sin_addr;
	struct in6_addr *addr6 = &((struct sockaddr_in6 *)&ss)->sin6_addr;

	switch (ss.ss_family) {
	case AF_INET:
		return addr4->s_addr == htonl(INADDR_ANY);
	case AF_INET6:
		return ipv6_addr_any(addr6);
	default:
		return true;
	}
}