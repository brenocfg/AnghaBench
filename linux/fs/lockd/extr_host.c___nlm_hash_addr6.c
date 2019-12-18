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
struct in6_addr {int /*<<< orphan*/ * s6_addr32; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 unsigned int __nlm_hash32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int __nlm_hash_addr6(const struct sockaddr *sap)
{
	const struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sap;
	const struct in6_addr addr = sin6->sin6_addr;
	return __nlm_hash32(addr.s6_addr32[0]) ^
	       __nlm_hash32(addr.s6_addr32[1]) ^
	       __nlm_hash32(addr.s6_addr32[2]) ^
	       __nlm_hash32(addr.s6_addr32[3]);
}