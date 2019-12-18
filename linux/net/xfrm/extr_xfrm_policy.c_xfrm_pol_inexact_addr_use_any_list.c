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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 scalar_t__ INEXACT_PREFIXLEN_IPV4 ; 
 scalar_t__ INEXACT_PREFIXLEN_IPV6 ; 
 scalar_t__ xfrm_addr_any (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool xfrm_pol_inexact_addr_use_any_list(const xfrm_address_t *addr,
					       int family, u8 prefixlen)
{
	if (xfrm_addr_any(addr, family))
		return true;

	if (family == AF_INET6 && prefixlen < INEXACT_PREFIXLEN_IPV6)
		return true;

	if (family == AF_INET && prefixlen < INEXACT_PREFIXLEN_IPV4)
		return true;

	return false;
}