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
 int AF_INET6 ; 
 char* strchr (char*,char) ; 

void
clean_ipv6_addr(int addr_family, char *addr)
{
#ifdef HAVE_IPV6
	if (addr_family == AF_INET6)
	{
		char	   *pct = strchr(addr, '%');

		if (pct)
			*pct = '\0';
	}
#endif
}