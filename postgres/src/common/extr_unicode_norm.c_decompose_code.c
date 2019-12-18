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
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ pg_wchar ;
typedef  int /*<<< orphan*/  pg_unicode_decomposition ;

/* Variables and functions */
 scalar_t__ DECOMPOSITION_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ LBASE ; 
 scalar_t__ SBASE ; 
 scalar_t__ SCOUNT ; 
 scalar_t__ TBASE ; 
 scalar_t__ TCOUNT ; 
 scalar_t__ VBASE ; 
 scalar_t__ VCOUNT ; 
 scalar_t__* get_code_decomposition (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * get_code_entry (scalar_t__) ; 

__attribute__((used)) static void
decompose_code(pg_wchar code, pg_wchar **result, int *current)
{
	pg_unicode_decomposition *entry;
	int			i;
	const uint32 *decomp;
	int			dec_size;

	/*
	 * Fast path for Hangul characters not stored in tables to save memory as
	 * decomposition is algorithmic. See
	 * https://www.unicode.org/reports/tr15/tr15-18.html, annex 10 for details on
	 * the matter.
	 */
	if (code >= SBASE && code < SBASE + SCOUNT)
	{
		uint32		l,
					v,
					tindex,
					sindex;
		pg_wchar   *res = *result;

		sindex = code - SBASE;
		l = LBASE + sindex / (VCOUNT * TCOUNT);
		v = VBASE + (sindex % (VCOUNT * TCOUNT)) / TCOUNT;
		tindex = sindex % TCOUNT;

		res[*current] = l;
		(*current)++;
		res[*current] = v;
		(*current)++;

		if (tindex != 0)
		{
			res[*current] = TBASE + tindex;
			(*current)++;
		}

		return;
	}

	entry = get_code_entry(code);

	/*
	 * Just fill in with the current decomposition if there are no
	 * decomposition codes to recurse to.  A NULL entry is equivalent to a
	 * character with class 0 and no decompositions, so just leave also in
	 * this case.
	 */
	if (entry == NULL || DECOMPOSITION_SIZE(entry) == 0)
	{
		pg_wchar   *res = *result;

		res[*current] = code;
		(*current)++;
		return;
	}

	/*
	 * If this entry has other decomposition codes look at them as well.
	 */
	decomp = get_code_decomposition(entry, &dec_size);
	for (i = 0; i < dec_size; i++)
	{
		pg_wchar	lcode = (pg_wchar) decomp[i];

		/* Leave if no more decompositions */
		decompose_code(lcode, result, current);
	}
}