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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  TextPositionState ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_position_cleanup (int /*<<< orphan*/ *) ; 
 int text_position_get_match_pos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_position_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_position_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
text_position(text *t1, text *t2, Oid collid)
{
	TextPositionState state;
	int			result;

	/* Empty needle always matches at position 1 */
	if (VARSIZE_ANY_EXHDR(t2) < 1)
		return 1;

	/* Otherwise, can't match if haystack is shorter than needle */
	if (VARSIZE_ANY_EXHDR(t1) < VARSIZE_ANY_EXHDR(t2))
		return 0;

	text_position_setup(t1, t2, collid, &state);
	if (!text_position_next(&state))
		result = 0;
	else
		result = text_position_get_match_pos(&state);
	text_position_cleanup(&state);
	return result;
}