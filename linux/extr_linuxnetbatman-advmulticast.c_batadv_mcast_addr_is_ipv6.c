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
typedef  int u8 ;
typedef  int /*<<< orphan*/  prefix ;

/* Variables and functions */
 scalar_t__ memcmp (int const*,int const*,int) ; 

__attribute__((used)) static bool batadv_mcast_addr_is_ipv6(const u8 *addr)
{
	static const u8 prefix[] = {0x33, 0x33};

	return memcmp(prefix, addr, sizeof(prefix)) == 0;
}