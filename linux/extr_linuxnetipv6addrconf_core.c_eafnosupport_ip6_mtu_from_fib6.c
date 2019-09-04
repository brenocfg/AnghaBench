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
typedef  int /*<<< orphan*/  u32 ;
struct in6_addr {int dummy; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32
eafnosupport_ip6_mtu_from_fib6(struct fib6_info *f6i, struct in6_addr *daddr,
			       struct in6_addr *saddr)
{
	return 0;
}