#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  count; TYPE_1__* lex; } ;
struct TYPE_3__ {int lex_level; } ;
typedef  TYPE_2__ AlenState ;

/* Variables and functions */

__attribute__((used)) static void
alen_array_element_start(void *state, bool isnull)
{
	AlenState  *_state = (AlenState *) state;

	/* just count up all the level 1 elements */
	if (_state->lex->lex_level == 1)
		_state->count++;
}