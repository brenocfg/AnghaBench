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
struct TYPE_4__ {scalar_t__ npath; TYPE_1__* lex; int /*<<< orphan*/  result_start; } ;
struct TYPE_3__ {int lex_level; int /*<<< orphan*/  token_start; } ;
typedef  TYPE_2__ GetState ;

/* Variables and functions */

__attribute__((used)) static void
get_object_start(void *state)
{
	GetState   *_state = (GetState *) state;
	int			lex_level = _state->lex->lex_level;

	if (lex_level == 0 && _state->npath == 0)
	{
		/*
		 * Special case: we should match the entire object.  We only need this
		 * at outermost level because at nested levels the match will have
		 * been started by the outer field or array element callback.
		 */
		_state->result_start = _state->lex->token_start;
	}
}