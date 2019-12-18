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
struct TYPE_2__ {int s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;

/* Variables and functions */

__attribute__((used)) static int
range_sockaddr_AF_INET(const struct sockaddr_in *addr,
					   const struct sockaddr_in *netaddr,
					   const struct sockaddr_in *netmask)
{
	if (((addr->sin_addr.s_addr ^ netaddr->sin_addr.s_addr) &
		 netmask->sin_addr.s_addr) == 0)
		return 1;
	else
		return 0;
}