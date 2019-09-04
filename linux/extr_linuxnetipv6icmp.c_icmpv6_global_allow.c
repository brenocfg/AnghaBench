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
 scalar_t__ icmp_global_allow () ; 
 scalar_t__ icmpv6_mask_allow (int) ; 

__attribute__((used)) static bool icmpv6_global_allow(int type)
{
	if (icmpv6_mask_allow(type))
		return true;

	if (icmp_global_allow())
		return true;

	return false;
}