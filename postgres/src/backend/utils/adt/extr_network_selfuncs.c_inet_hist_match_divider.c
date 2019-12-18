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
 int Min (int,int) ; 
 int bitncommon (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ inet_masklen_inclusion_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ip_addr (int /*<<< orphan*/ *) ; 
 int ip_bits (int /*<<< orphan*/ *) ; 
 scalar_t__ ip_family (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
inet_hist_match_divider(inet *boundary, inet *query, int opr_codenum)
{
	if (ip_family(boundary) == ip_family(query) &&
		inet_masklen_inclusion_cmp(boundary, query, opr_codenum) == 0)
	{
		int			min_bits,
					decisive_bits;

		min_bits = Min(ip_bits(boundary), ip_bits(query));

		/*
		 * Set decisive_bits to the masklen of the one that should contain the
		 * other according to the operator.
		 */
		if (opr_codenum < 0)
			decisive_bits = ip_bits(boundary);
		else if (opr_codenum > 0)
			decisive_bits = ip_bits(query);
		else
			decisive_bits = min_bits;

		/*
		 * Now return the number of non-common decisive bits.  (This will be
		 * zero if the boundary and query in fact match, else positive.)
		 */
		if (min_bits > 0)
			return decisive_bits - bitncommon(ip_addr(boundary),
											  ip_addr(query),
											  min_bits);
		return decisive_bits;
	}

	return -1;
}