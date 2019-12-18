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
typedef  char uint32 ;
typedef  char pg_wchar ;
struct TYPE_3__ {int comb_class; } ;
typedef  TYPE_1__ pg_unicode_decomposition ;

/* Variables and functions */
 scalar_t__ ALLOC (int) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  decompose_code (char const,char**,int*) ; 
 TYPE_1__* get_code_entry (char) ; 
 scalar_t__ get_decomposed_size (char const) ; 
 scalar_t__ recompose_code (char,char,char*) ; 

pg_wchar *
unicode_normalize_kc(const pg_wchar *input)
{
	pg_wchar   *decomp_chars;
	pg_wchar   *recomp_chars;
	int			decomp_size,
				current_size;
	int			count;
	const pg_wchar *p;

	/* variables for recomposition */
	int			last_class;
	int			starter_pos;
	int			target_pos;
	uint32		starter_ch;

	/* First, do character decomposition */

	/*
	 * Calculate how many characters long the decomposed version will be.
	 */
	decomp_size = 0;
	for (p = input; *p; p++)
		decomp_size += get_decomposed_size(*p);

	decomp_chars = (pg_wchar *) ALLOC((decomp_size + 1) * sizeof(pg_wchar));
	if (decomp_chars == NULL)
		return NULL;

	/*
	 * Now fill in each entry recursively. This needs a second pass on the
	 * decomposition table.
	 */
	current_size = 0;
	for (p = input; *p; p++)
		decompose_code(*p, &decomp_chars, &current_size);
	decomp_chars[decomp_size] = '\0';
	Assert(decomp_size == current_size);

	/*
	 * Now apply canonical ordering.
	 */
	for (count = 1; count < decomp_size; count++)
	{
		pg_wchar	prev = decomp_chars[count - 1];
		pg_wchar	next = decomp_chars[count];
		pg_wchar	tmp;
		pg_unicode_decomposition *prevEntry = get_code_entry(prev);
		pg_unicode_decomposition *nextEntry = get_code_entry(next);

		/*
		 * If no entries are found, the character used is either an Hangul
		 * character or a character with a class of 0 and no decompositions,
		 * so move to next result.
		 */
		if (prevEntry == NULL || nextEntry == NULL)
			continue;

		/*
		 * Per Unicode (https://www.unicode.org/reports/tr15/tr15-18.html) annex 4,
		 * a sequence of two adjacent characters in a string is an
		 * exchangeable pair if the combining class (from the Unicode
		 * Character Database) for the first character is greater than the
		 * combining class for the second, and the second is not a starter.  A
		 * character is a starter if its combining class is 0.
		 */
		if (nextEntry->comb_class == 0x0 || prevEntry->comb_class == 0x0)
			continue;

		if (prevEntry->comb_class <= nextEntry->comb_class)
			continue;

		/* exchange can happen */
		tmp = decomp_chars[count - 1];
		decomp_chars[count - 1] = decomp_chars[count];
		decomp_chars[count] = tmp;

		/* backtrack to check again */
		if (count > 1)
			count -= 2;
	}

	/*
	 * The last phase of NFKC is the recomposition of the reordered Unicode
	 * string using combining classes. The recomposed string cannot be longer
	 * than the decomposed one, so make the allocation of the output string
	 * based on that assumption.
	 */
	recomp_chars = (pg_wchar *) ALLOC((decomp_size + 1) * sizeof(pg_wchar));
	if (!recomp_chars)
	{
		FREE(decomp_chars);
		return NULL;
	}

	last_class = -1;			/* this eliminates a special check */
	starter_pos = 0;
	target_pos = 1;
	starter_ch = recomp_chars[0] = decomp_chars[0];

	for (count = 1; count < decomp_size; count++)
	{
		pg_wchar	ch = decomp_chars[count];
		pg_unicode_decomposition *ch_entry = get_code_entry(ch);
		int			ch_class = (ch_entry == NULL) ? 0 : ch_entry->comb_class;
		pg_wchar	composite;

		if (last_class < ch_class &&
			recompose_code(starter_ch, ch, &composite))
		{
			recomp_chars[starter_pos] = composite;
			starter_ch = composite;
		}
		else if (ch_class == 0)
		{
			starter_pos = target_pos;
			starter_ch = ch;
			last_class = -1;
			recomp_chars[target_pos++] = ch;
		}
		else
		{
			last_class = ch_class;
			recomp_chars[target_pos++] = ch;
		}
	}
	recomp_chars[target_pos] = (pg_wchar) '\0';

	FREE(decomp_chars);

	return recomp_chars;
}