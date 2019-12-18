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
typedef  int int32 ;
typedef  int /*<<< orphan*/  inet ;

/* Variables and functions */
 int /*<<< orphan*/  Min (scalar_t__,scalar_t__) ; 
 int bitncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ ip_bits (int /*<<< orphan*/ *) ; 
 int ip_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_maxbits (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32
network_cmp_internal(inet *a1, inet *a2)
{
	if (ip_family(a1) == ip_family(a2))
	{
		int			order;

		order = bitncmp(ip_addr(a1), ip_addr(a2),
						Min(ip_bits(a1), ip_bits(a2)));
		if (order != 0)
			return order;
		order = ((int) ip_bits(a1)) - ((int) ip_bits(a2));
		if (order != 0)
			return order;
		return bitncmp(ip_addr(a1), ip_addr(a2), ip_maxbits(a1));
	}

	return ip_family(a1) - ip_family(a2);
}