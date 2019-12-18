#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const inet ;
struct TYPE_3__ {int sk_strategy; int /*<<< orphan*/  sk_argument; } ;
typedef  int StrategyNumber ;
typedef  TYPE_1__* ScanKey ;

/* Variables and functions */
 int /*<<< orphan*/  const* DatumGetInetPP (int /*<<< orphan*/ ) ; 
 int Min (int,int) ; 
#define  RTEqualStrategyNumber 137 
#define  RTGreaterEqualStrategyNumber 136 
#define  RTGreaterStrategyNumber 135 
#define  RTLessEqualStrategyNumber 134 
#define  RTLessStrategyNumber 133 
#define  RTNotEqualStrategyNumber 132 
#define  RTSubEqualStrategyNumber 131 
#define  RTSubStrategyNumber 130 
#define  RTSuperEqualStrategyNumber 129 
#define  RTSuperStrategyNumber 128 
 int bitncmp (int*,int*,int) ; 
 int* ip_addr (int /*<<< orphan*/  const*) ; 
 int ip_bits (int /*<<< orphan*/  const*) ; 
 scalar_t__ ip_family (int /*<<< orphan*/  const*) ; 
 int ip_maxbits (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
inet_spg_consistent_bitmap(const inet *prefix, int nkeys, ScanKey scankeys,
						   bool leaf)
{
	int			bitmap;
	int			commonbits,
				i;

	/* Initialize result to allow visiting all children */
	if (leaf)
		bitmap = 1;
	else
		bitmap = 1 | (1 << 1) | (1 << 2) | (1 << 3);

	commonbits = ip_bits(prefix);

	for (i = 0; i < nkeys; i++)
	{
		inet	   *argument = DatumGetInetPP(scankeys[i].sk_argument);
		StrategyNumber strategy = scankeys[i].sk_strategy;
		int			order;

		/*
		 * Check 0: different families
		 *
		 * Matching families do not help any of the strategies.
		 */
		if (ip_family(argument) != ip_family(prefix))
		{
			switch (strategy)
			{
				case RTLessStrategyNumber:
				case RTLessEqualStrategyNumber:
					if (ip_family(argument) < ip_family(prefix))
						bitmap = 0;
					break;

				case RTGreaterEqualStrategyNumber:
				case RTGreaterStrategyNumber:
					if (ip_family(argument) > ip_family(prefix))
						bitmap = 0;
					break;

				case RTNotEqualStrategyNumber:
					break;

				default:
					/* For all other cases, we can be sure there is no match */
					bitmap = 0;
					break;
			}

			if (!bitmap)
				break;

			/* Other checks make no sense with different families. */
			continue;
		}

		/*
		 * Check 1: network bit count
		 *
		 * Network bit count (ip_bits) helps to check leaves for sub network
		 * and sup network operators.  At non-leaf nodes, we know every child
		 * value has greater ip_bits, so we can avoid descending in some cases
		 * too.
		 *
		 * This check is less expensive than checking the address bits, so we
		 * are doing this before, but it has to be done after for the basic
		 * comparison strategies, because ip_bits only affect their results
		 * when the common network bits are the same.
		 */
		switch (strategy)
		{
			case RTSubStrategyNumber:
				if (commonbits <= ip_bits(argument))
					bitmap &= (1 << 2) | (1 << 3);
				break;

			case RTSubEqualStrategyNumber:
				if (commonbits < ip_bits(argument))
					bitmap &= (1 << 2) | (1 << 3);
				break;

			case RTSuperStrategyNumber:
				if (commonbits == ip_bits(argument) - 1)
					bitmap &= 1 | (1 << 1);
				else if (commonbits >= ip_bits(argument))
					bitmap = 0;
				break;

			case RTSuperEqualStrategyNumber:
				if (commonbits == ip_bits(argument))
					bitmap &= 1 | (1 << 1);
				else if (commonbits > ip_bits(argument))
					bitmap = 0;
				break;

			case RTEqualStrategyNumber:
				if (commonbits < ip_bits(argument))
					bitmap &= (1 << 2) | (1 << 3);
				else if (commonbits == ip_bits(argument))
					bitmap &= 1 | (1 << 1);
				else
					bitmap = 0;
				break;
		}

		if (!bitmap)
			break;

		/*
		 * Check 2: common network bits
		 *
		 * Compare available common prefix bits to the query, but not beyond
		 * either the query's netmask or the minimum netmask among the
		 * represented values.  If these bits don't match the query, we can
		 * eliminate some cases.
		 */
		order = bitncmp(ip_addr(prefix), ip_addr(argument),
						Min(commonbits, ip_bits(argument)));

		if (order != 0)
		{
			switch (strategy)
			{
				case RTLessStrategyNumber:
				case RTLessEqualStrategyNumber:
					if (order > 0)
						bitmap = 0;
					break;

				case RTGreaterEqualStrategyNumber:
				case RTGreaterStrategyNumber:
					if (order < 0)
						bitmap = 0;
					break;

				case RTNotEqualStrategyNumber:
					break;

				default:
					/* For all other cases, we can be sure there is no match */
					bitmap = 0;
					break;
			}

			if (!bitmap)
				break;

			/*
			 * Remaining checks make no sense when common bits don't match.
			 */
			continue;
		}

		/*
		 * Check 3: next network bit
		 *
		 * We can filter out branch 2 or 3 using the next network bit of the
		 * argument, if it is available.
		 *
		 * This check matters for the performance of the search. The results
		 * would be correct without it.
		 */
		if (bitmap & ((1 << 2) | (1 << 3)) &&
			commonbits < ip_bits(argument))
		{
			int			nextbit;

			nextbit = ip_addr(argument)[commonbits / 8] &
				(1 << (7 - commonbits % 8));

			switch (strategy)
			{
				case RTLessStrategyNumber:
				case RTLessEqualStrategyNumber:
					if (!nextbit)
						bitmap &= 1 | (1 << 1) | (1 << 2);
					break;

				case RTGreaterEqualStrategyNumber:
				case RTGreaterStrategyNumber:
					if (nextbit)
						bitmap &= 1 | (1 << 1) | (1 << 3);
					break;

				case RTNotEqualStrategyNumber:
					break;

				default:
					if (!nextbit)
						bitmap &= 1 | (1 << 1) | (1 << 2);
					else
						bitmap &= 1 | (1 << 1) | (1 << 3);
					break;
			}

			if (!bitmap)
				break;
		}

		/*
		 * Remaining checks are only for the basic comparison strategies. This
		 * test relies on the strategy number ordering defined in stratnum.h.
		 */
		if (strategy < RTEqualStrategyNumber ||
			strategy > RTGreaterEqualStrategyNumber)
			continue;

		/*
		 * Check 4: network bit count
		 *
		 * At this point, we know that the common network bits of the prefix
		 * and the argument are the same, so we can go forward and check the
		 * ip_bits.
		 */
		switch (strategy)
		{
			case RTLessStrategyNumber:
			case RTLessEqualStrategyNumber:
				if (commonbits == ip_bits(argument))
					bitmap &= 1 | (1 << 1);
				else if (commonbits > ip_bits(argument))
					bitmap = 0;
				break;

			case RTGreaterEqualStrategyNumber:
			case RTGreaterStrategyNumber:
				if (commonbits < ip_bits(argument))
					bitmap &= (1 << 2) | (1 << 3);
				break;
		}

		if (!bitmap)
			break;

		/* Remaining checks don't make sense with different ip_bits. */
		if (commonbits != ip_bits(argument))
			continue;

		/*
		 * Check 5: next host bit
		 *
		 * We can filter out branch 0 or 1 using the next host bit of the
		 * argument, if it is available.
		 *
		 * This check matters for the performance of the search. The results
		 * would be correct without it.  There is no point in running it for
		 * leafs as we have to check the whole address on the next step.
		 */
		if (!leaf && bitmap & (1 | (1 << 1)) &&
			commonbits < ip_maxbits(argument))
		{
			int			nextbit;

			nextbit = ip_addr(argument)[commonbits / 8] &
				(1 << (7 - commonbits % 8));

			switch (strategy)
			{
				case RTLessStrategyNumber:
				case RTLessEqualStrategyNumber:
					if (!nextbit)
						bitmap &= 1 | (1 << 2) | (1 << 3);
					break;

				case RTGreaterEqualStrategyNumber:
				case RTGreaterStrategyNumber:
					if (nextbit)
						bitmap &= (1 << 1) | (1 << 2) | (1 << 3);
					break;

				case RTNotEqualStrategyNumber:
					break;

				default:
					if (!nextbit)
						bitmap &= 1 | (1 << 2) | (1 << 3);
					else
						bitmap &= (1 << 1) | (1 << 2) | (1 << 3);
					break;
			}

			if (!bitmap)
				break;
		}

		/*
		 * Check 6: whole address
		 *
		 * This is the last check for correctness of the basic comparison
		 * strategies.  It's only appropriate at leaf entries.
		 */
		if (leaf)
		{
			/* Redo ordering comparison using all address bits */
			order = bitncmp(ip_addr(prefix), ip_addr(argument),
							ip_maxbits(prefix));

			switch (strategy)
			{
				case RTLessStrategyNumber:
					if (order >= 0)
						bitmap = 0;
					break;

				case RTLessEqualStrategyNumber:
					if (order > 0)
						bitmap = 0;
					break;

				case RTEqualStrategyNumber:
					if (order != 0)
						bitmap = 0;
					break;

				case RTGreaterEqualStrategyNumber:
					if (order < 0)
						bitmap = 0;
					break;

				case RTGreaterStrategyNumber:
					if (order <= 0)
						bitmap = 0;
					break;

				case RTNotEqualStrategyNumber:
					if (order == 0)
						bitmap = 0;
					break;
			}

			if (!bitmap)
				break;
		}
	}

	return bitmap;
}