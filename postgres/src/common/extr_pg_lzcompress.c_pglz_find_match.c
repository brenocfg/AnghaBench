#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
typedef  size_t int16 ;
struct TYPE_4__ {char* pos; struct TYPE_4__* next; } ;
typedef  TYPE_1__ PGLZ_HistEntry ;

/* Variables and functions */
 TYPE_1__* INVALID_ENTRY_PTR ; 
 int PGLZ_MAX_MATCH ; 
 TYPE_1__* hist_entries ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 size_t pglz_hist_idx (char const*,char const*,int) ; 

__attribute__((used)) static inline int
pglz_find_match(int16 *hstart, const char *input, const char *end,
				int *lenp, int *offp, int good_match, int good_drop, int mask)
{
	PGLZ_HistEntry *hent;
	int16		hentno;
	int32		len = 0;
	int32		off = 0;

	/*
	 * Traverse the linked history list until a good enough match is found.
	 */
	hentno = hstart[pglz_hist_idx(input, end, mask)];
	hent = &hist_entries[hentno];
	while (hent != INVALID_ENTRY_PTR)
	{
		const char *ip = input;
		const char *hp = hent->pos;
		int32		thisoff;
		int32		thislen;

		/*
		 * Stop if the offset does not fit into our tag anymore.
		 */
		thisoff = ip - hp;
		if (thisoff >= 0x0fff)
			break;

		/*
		 * Determine length of match. A better match must be larger than the
		 * best so far. And if we already have a match of 16 or more bytes,
		 * it's worth the call overhead to use memcmp() to check if this match
		 * is equal for the same size. After that we must fallback to
		 * character by character comparison to know the exact position where
		 * the diff occurred.
		 */
		thislen = 0;
		if (len >= 16)
		{
			if (memcmp(ip, hp, len) == 0)
			{
				thislen = len;
				ip += len;
				hp += len;
				while (ip < end && *ip == *hp && thislen < PGLZ_MAX_MATCH)
				{
					thislen++;
					ip++;
					hp++;
				}
			}
		}
		else
		{
			while (ip < end && *ip == *hp && thislen < PGLZ_MAX_MATCH)
			{
				thislen++;
				ip++;
				hp++;
			}
		}

		/*
		 * Remember this match as the best (if it is)
		 */
		if (thislen > len)
		{
			len = thislen;
			off = thisoff;
		}

		/*
		 * Advance to the next history entry
		 */
		hent = hent->next;

		/*
		 * Be happy with lesser good matches the more entries we visited. But
		 * no point in doing calculation if we're at end of list.
		 */
		if (hent != INVALID_ENTRY_PTR)
		{
			if (len >= good_match)
				break;
			good_match -= (good_match * good_drop) / 100;
		}
	}

	/*
	 * Return match information only if it results at least in one byte
	 * reduction.
	 */
	if (len > 2)
	{
		*lenp = len;
		*offp = off;
		return 1;
	}

	return 0;
}