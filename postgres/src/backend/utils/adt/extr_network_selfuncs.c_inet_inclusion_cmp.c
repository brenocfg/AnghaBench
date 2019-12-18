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
typedef  int /*<<< orphan*/  inet ;

/* Variables and functions */
 int /*<<< orphan*/  Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bitncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inet_masklen_inclusion_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ip_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_bits (int /*<<< orphan*/ *) ; 
 int ip_family (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
inet_inclusion_cmp(inet *left, inet *right, int opr_codenum)
{
	if (ip_family(left) == ip_family(right))
	{
		int			order;

		order = bitncmp(ip_addr(left), ip_addr(right),
						Min(ip_bits(left), ip_bits(right)));
		if (order != 0)
			return order;

		return inet_masklen_inclusion_cmp(left, right, opr_codenum);
	}

	return ip_family(left) - ip_family(right);
}