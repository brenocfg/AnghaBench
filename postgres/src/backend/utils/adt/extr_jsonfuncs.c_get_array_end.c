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
struct TYPE_4__ {scalar_t__ npath; char* result_start; int /*<<< orphan*/  tresult; TYPE_1__* lex; } ;
struct TYPE_3__ {int lex_level; char* prev_token_terminator; } ;
typedef  TYPE_2__ GetState ;

/* Variables and functions */
 int /*<<< orphan*/  cstring_to_text_with_len (char*,int) ; 

__attribute__((used)) static void
get_array_end(void *state)
{
	GetState   *_state = (GetState *) state;
	int			lex_level = _state->lex->lex_level;

	if (lex_level == 0 && _state->npath == 0)
	{
		/* Special case: return the entire array */
		char	   *start = _state->result_start;
		int			len = _state->lex->prev_token_terminator - start;

		_state->tresult = cstring_to_text_with_len(start, len);
	}
}