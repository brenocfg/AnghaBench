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
typedef  scalar_t__ __be32 ;

/* Variables and functions */

__attribute__((used)) static bool ipv4_rcv_saddr_equal(__be32 sk1_rcv_saddr, __be32 sk2_rcv_saddr,
				 bool sk2_ipv6only, bool match_wildcard)
{
	if (!sk2_ipv6only) {
		if (sk1_rcv_saddr == sk2_rcv_saddr)
			return true;
		if (!sk1_rcv_saddr || !sk2_rcv_saddr)
			return match_wildcard;
	}
	return false;
}