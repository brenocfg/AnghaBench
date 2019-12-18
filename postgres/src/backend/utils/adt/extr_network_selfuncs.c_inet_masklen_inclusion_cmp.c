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
 scalar_t__ ip_bits (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
inet_masklen_inclusion_cmp(inet *left, inet *right, int opr_codenum)
{
	int			order;

	order = (int) ip_bits(left) - (int) ip_bits(right);

	/*
	 * Return 0 if the operator would accept this combination of masklens.
	 * Note that opr_codenum zero (overlaps) will accept all cases.
	 */
	if ((order > 0 && opr_codenum >= 0) ||
		(order == 0 && opr_codenum >= -1 && opr_codenum <= 1) ||
		(order < 0 && opr_codenum <= 0))
		return 0;

	/*
	 * Otherwise, return a negative value for sup/supeq (notionally, the RHS
	 * needs to have a larger masklen than it has, which would make it sort
	 * later), or a positive value for sub/subeq (vice versa).
	 */
	return opr_codenum;
}