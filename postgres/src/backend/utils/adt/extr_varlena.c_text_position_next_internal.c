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
struct TYPE_3__ {int len1; int len2; int skiptablemask; char* str1; char* str2; int /*<<< orphan*/ * skiptable; } ;
typedef  TYPE_1__ TextPositionState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

__attribute__((used)) static char *
text_position_next_internal(char *start_ptr, TextPositionState *state)
{
	int			haystack_len = state->len1;
	int			needle_len = state->len2;
	int			skiptablemask = state->skiptablemask;
	const char *haystack = state->str1;
	const char *needle = state->str2;
	const char *haystack_end = &haystack[haystack_len];
	const char *hptr;

	Assert(start_ptr >= haystack && start_ptr <= haystack_end);

	if (needle_len == 1)
	{
		/* No point in using B-M-H for a one-character needle */
		char		nchar = *needle;

		hptr = start_ptr;
		while (hptr < haystack_end)
		{
			if (*hptr == nchar)
				return (char *) hptr;
			hptr++;
		}
	}
	else
	{
		const char *needle_last = &needle[needle_len - 1];

		/* Start at startpos plus the length of the needle */
		hptr = start_ptr + needle_len - 1;
		while (hptr < haystack_end)
		{
			/* Match the needle scanning *backward* */
			const char *nptr;
			const char *p;

			nptr = needle_last;
			p = hptr;
			while (*nptr == *p)
			{
				/* Matched it all?	If so, return 1-based position */
				if (nptr == needle)
					return (char *) p;
				nptr--, p--;
			}

			/*
			 * No match, so use the haystack char at hptr to decide how far to
			 * advance.  If the needle had any occurrence of that character
			 * (or more precisely, one sharing the same skiptable entry)
			 * before its last character, then we advance far enough to align
			 * the last such needle character with that haystack position.
			 * Otherwise we can advance by the whole needle length.
			 */
			hptr += state->skiptable[(unsigned char) *hptr & skiptablemask];
		}
	}

	return 0;					/* not found */
}