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
struct in6_addr {scalar_t__* s6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int NETMASK ; 
 int inet_pton (int /*<<< orphan*/ ,char*,struct in6_addr*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static int expand_ipv6(char *addr, int type)
{
	int ret;
	struct in6_addr v6_addr;

	ret = inet_pton(AF_INET6, addr, &v6_addr);

	if (ret != 1) {
		if (type == NETMASK)
			return 1;
		return 0;
	}

	sprintf(addr, "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:"
		"%02x%02x:%02x%02x:%02x%02x",
		(int)v6_addr.s6_addr[0], (int)v6_addr.s6_addr[1],
		(int)v6_addr.s6_addr[2], (int)v6_addr.s6_addr[3],
		(int)v6_addr.s6_addr[4], (int)v6_addr.s6_addr[5],
		(int)v6_addr.s6_addr[6], (int)v6_addr.s6_addr[7],
		(int)v6_addr.s6_addr[8], (int)v6_addr.s6_addr[9],
		(int)v6_addr.s6_addr[10], (int)v6_addr.s6_addr[11],
		(int)v6_addr.s6_addr[12], (int)v6_addr.s6_addr[13],
		(int)v6_addr.s6_addr[14], (int)v6_addr.s6_addr[15]);

	return 1;

}