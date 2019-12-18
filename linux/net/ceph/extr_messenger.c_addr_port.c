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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  ss_family; } ;
struct ceph_entity_addr {TYPE_1__ in_addr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int get_unaligned (int /*<<< orphan*/ *) ; 
 int ntohs (int) ; 

__attribute__((used)) static int addr_port(struct ceph_entity_addr *addr)
{
	switch (get_unaligned(&addr->in_addr.ss_family)) {
	case AF_INET:
		return ntohs(get_unaligned(&((struct sockaddr_in *)&addr->in_addr)->sin_port));
	case AF_INET6:
		return ntohs(get_unaligned(&((struct sockaddr_in6 *)&addr->in_addr)->sin6_port));
	}
	return 0;
}