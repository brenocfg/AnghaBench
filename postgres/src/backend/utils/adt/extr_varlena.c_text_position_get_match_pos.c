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
struct TYPE_3__ {int last_match; int str1; scalar_t__ refpoint; int refpos; int /*<<< orphan*/  is_multibyte; } ;
typedef  TYPE_1__ TextPositionState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ pg_mblen (scalar_t__) ; 

__attribute__((used)) static int
text_position_get_match_pos(TextPositionState *state)
{
	if (!state->is_multibyte)
		return state->last_match - state->str1 + 1;
	else
	{
		/* Convert the byte position to char position. */
		while (state->refpoint < state->last_match)
		{
			state->refpoint += pg_mblen(state->refpoint);
			state->refpos++;
		}
		Assert(state->refpoint == state->last_match);
		return state->refpos + 1;
	}
}