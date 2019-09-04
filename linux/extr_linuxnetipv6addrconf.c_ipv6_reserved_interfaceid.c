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
struct in6_addr {int* s6_addr32; } ;

/* Variables and functions */
 int htonl (int) ; 

__attribute__((used)) static bool ipv6_reserved_interfaceid(struct in6_addr address)
{
	if ((address.s6_addr32[2] | address.s6_addr32[3]) == 0)
		return true;

	if (address.s6_addr32[2] == htonl(0x02005eff) &&
	    ((address.s6_addr32[3] & htonl(0xfe000000)) == htonl(0xfe000000)))
		return true;

	if (address.s6_addr32[2] == htonl(0xfdffffff) &&
	    ((address.s6_addr32[3] & htonl(0xffffff80)) == htonl(0xffffff80)))
		return true;

	return false;
}