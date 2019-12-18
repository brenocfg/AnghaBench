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
struct TYPE_4__ {int len2; char* last_match; char* str1; char* refpoint; int /*<<< orphan*/  refpos; scalar_t__ is_multibyte_char_in_char; } ;
typedef  TYPE_1__ TextPositionState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  pg_mblen (char*) ; 
 char* text_position_next_internal (char*,TYPE_1__*) ; 

__attribute__((used)) static bool
text_position_next(TextPositionState *state)
{
	int			needle_len = state->len2;
	char	   *start_ptr;
	char	   *matchptr;

	if (needle_len <= 0)
		return false;			/* result for empty pattern */

	/* Start from the point right after the previous match. */
	if (state->last_match)
		start_ptr = state->last_match + needle_len;
	else
		start_ptr = state->str1;

retry:
	matchptr = text_position_next_internal(start_ptr, state);

	if (!matchptr)
		return false;

	/*
	 * Found a match for the byte sequence.  If this is a multibyte encoding,
	 * where one character's byte sequence can appear inside a longer
	 * multi-byte character, we need to verify that the match was at a
	 * character boundary, not in the middle of a multi-byte character.
	 */
	if (state->is_multibyte_char_in_char)
	{
		/* Walk one character at a time, until we reach the match. */

		/* the search should never move backwards. */
		Assert(state->refpoint <= matchptr);

		while (state->refpoint < matchptr)
		{
			/* step to next character. */
			state->refpoint += pg_mblen(state->refpoint);
			state->refpos++;

			/*
			 * If we stepped over the match's start position, then it was a
			 * false positive, where the byte sequence appeared in the middle
			 * of a multi-byte character.  Skip it, and continue the search at
			 * the next character boundary.
			 */
			if (state->refpoint > matchptr)
			{
				start_ptr = state->refpoint;
				goto retry;
			}
		}
	}

	state->last_match = matchptr;
	return true;
}