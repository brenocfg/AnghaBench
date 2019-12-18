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
struct TYPE_4__ {int next_scalar; TYPE_1__* lex; int /*<<< orphan*/  result_start; scalar_t__ normalize_results; } ;
struct TYPE_3__ {int lex_level; scalar_t__ token_type; int /*<<< orphan*/  token_start; } ;
typedef  TYPE_2__ ElementsState ;

/* Variables and functions */
 scalar_t__ JSON_TOKEN_STRING ; 

__attribute__((used)) static void
elements_array_element_start(void *state, bool isnull)
{
	ElementsState *_state = (ElementsState *) state;

	/* save a pointer to where the value starts */
	if (_state->lex->lex_level == 1)
	{
		/*
		 * next_scalar will be reset in the array_element_end handler, and
		 * since we know the value is a scalar there is no danger of it being
		 * on while recursing down the tree.
		 */
		if (_state->normalize_results && _state->lex->token_type == JSON_TOKEN_STRING)
			_state->next_scalar = true;
		else
			_state->result_start = _state->lex->token_start;
	}
}