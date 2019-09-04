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
 int AF_INET ; 

__attribute__((used)) static bool ip_vs_is_af_valid(int af)
{
	if (af == AF_INET)
		return true;
#ifdef CONFIG_IP_VS_IPV6
	if (af == AF_INET6 && ipv6_mod_enabled())
		return true;
#endif
	return false;
}