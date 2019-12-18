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
 scalar_t__ SBASE ; 
 scalar_t__ SCOUNT ; 
 scalar_t__ TCOUNT ; 
 scalar_t__* get_code_decomposition (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * get_code_entry (scalar_t__) ; 

__attribute__((used)) static int
get_decomposed_size(pg_wchar code)
{
	pg_unicode_decomposition *entry;
	int			size = 0;
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
		uint32		tindex,
					sindex;

		sindex = code - SBASE;
		tindex = sindex % TCOUNT;

		if (tindex != 0)
			return 3;
		return 2;
	}

	entry = get_code_entry(code);

	/*
	 * Just count current code if no other decompositions.  A NULL entry is
	 * equivalent to a character with class 0 and no decompositions.
	 */
	if (entry == NULL || DECOMPOSITION_SIZE(entry) == 0)
		return 1;

	/*
	 * If this entry has other decomposition codes look at them as well. First
	 * get its decomposition in the list of tables available.
	 */
	decomp = get_code_decomposition(entry, &dec_size);
	for (i = 0; i < dec_size; i++)
	{
		uint32		lcode = decomp[i];

		size += get_decomposed_size(lcode);
	}

	return size;
}