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
 int ICMPV6_INFOMSG_MASK ; 
 int ICMPV6_PKT_TOOBIG ; 

__attribute__((used)) static bool icmpv6_mask_allow(int type)
{
	/* Informational messages are not limited. */
	if (type & ICMPV6_INFOMSG_MASK)
		return true;

	/* Do not limit pmtu discovery, it would break it. */
	if (type == ICMPV6_PKT_TOOBIG)
		return true;

	return false;
}