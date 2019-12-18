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
typedef  int /*<<< orphan*/  PageData ;

/* Variables and functions */
 int MATCH_THRESHOLD ; 
 int Min (int,int) ; 
 int /*<<< orphan*/  writeFragment (int /*<<< orphan*/ *,int,int,char const*) ; 

__attribute__((used)) static void
computeRegionDelta(PageData *pageData,
				   const char *curpage, const char *targetpage,
				   int targetStart, int targetEnd,
				   int validStart, int validEnd)
{
	int			i,
				loopEnd,
				fragmentBegin = -1,
				fragmentEnd = -1;

	/* Deal with any invalid start region by including it in first fragment */
	if (validStart > targetStart)
	{
		fragmentBegin = targetStart;
		targetStart = validStart;
	}

	/* We'll deal with any invalid end region after the main loop */
	loopEnd = Min(targetEnd, validEnd);

	/* Examine all the potentially matchable bytes */
	i = targetStart;
	while (i < loopEnd)
	{
		if (curpage[i] != targetpage[i])
		{
			/* On unmatched byte, start new fragment if not already in one */
			if (fragmentBegin < 0)
				fragmentBegin = i;
			/* Mark unmatched-data endpoint as uncertain */
			fragmentEnd = -1;
			/* Extend the fragment as far as possible in a tight loop */
			i++;
			while (i < loopEnd && curpage[i] != targetpage[i])
				i++;
			if (i >= loopEnd)
				break;
		}

		/* Found a matched byte, so remember end of unmatched fragment */
		fragmentEnd = i;

		/*
		 * Extend the match as far as possible in a tight loop.  (On typical
		 * workloads, this inner loop is the bulk of this function's runtime.)
		 */
		i++;
		while (i < loopEnd && curpage[i] == targetpage[i])
			i++;

		/*
		 * There are several possible cases at this point:
		 *
		 * 1. We have no unwritten fragment (fragmentBegin < 0).  There's
		 * nothing to write; and it doesn't matter what fragmentEnd is.
		 *
		 * 2. We found more than MATCH_THRESHOLD consecutive matching bytes.
		 * Dump out the unwritten fragment, stopping at fragmentEnd.
		 *
		 * 3. The match extends to loopEnd.  We'll do nothing here, exit the
		 * loop, and then dump the unwritten fragment, after merging it with
		 * the invalid end region if any.  If we don't so merge, fragmentEnd
		 * establishes how much the final writeFragment call needs to write.
		 *
		 * 4. We found an unmatched byte before loopEnd.  The loop will repeat
		 * and will enter the unmatched-byte stanza above.  So in this case
		 * also, it doesn't matter what fragmentEnd is.  The matched bytes
		 * will get merged into the continuing unmatched fragment.
		 *
		 * Only in case 3 do we reach the bottom of the loop with a meaningful
		 * fragmentEnd value, which is why it's OK that we unconditionally
		 * assign "fragmentEnd = i" above.
		 */
		if (fragmentBegin >= 0 && i - fragmentEnd > MATCH_THRESHOLD)
		{
			writeFragment(pageData, fragmentBegin,
						  fragmentEnd - fragmentBegin,
						  targetpage + fragmentBegin);
			fragmentBegin = -1;
			fragmentEnd = -1;	/* not really necessary */
		}
	}

	/* Deal with any invalid end region by including it in final fragment */
	if (loopEnd < targetEnd)
	{
		if (fragmentBegin < 0)
			fragmentBegin = loopEnd;
		fragmentEnd = targetEnd;
	}

	/* Write final fragment if any */
	if (fragmentBegin >= 0)
	{
		if (fragmentEnd < 0)
			fragmentEnd = targetEnd;
		writeFragment(pageData, fragmentBegin,
					  fragmentEnd - fragmentBegin,
					  targetpage + fragmentBegin);
	}
}