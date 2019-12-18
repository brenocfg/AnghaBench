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

/* Variables and functions */
 int IPV6_ADDR_COMPATv4 ; 
 int IPV6_ADDR_LOOPBACK ; 
 int IPV6_ADDR_MAPPED ; 

__attribute__((used)) static inline int ipv6_saddr_preferred(int type)
{
	if (type & (IPV6_ADDR_MAPPED|IPV6_ADDR_COMPATv4|IPV6_ADDR_LOOPBACK))
		return 1;
	return 0;
}