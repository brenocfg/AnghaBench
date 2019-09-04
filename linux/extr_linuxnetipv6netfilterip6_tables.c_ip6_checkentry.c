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
struct ip6t_ip6 {int flags; int invflags; } ;

/* Variables and functions */
 int IP6T_F_MASK ; 
 int IP6T_INV_MASK ; 

__attribute__((used)) static bool
ip6_checkentry(const struct ip6t_ip6 *ipv6)
{
	if (ipv6->flags & ~IP6T_F_MASK)
		return false;
	if (ipv6->invflags & ~IP6T_INV_MASK)
		return false;

	return true;
}