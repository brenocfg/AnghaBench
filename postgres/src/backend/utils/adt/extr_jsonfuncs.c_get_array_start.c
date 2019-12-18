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
struct TYPE_4__ {int lex_level; int /*<<< orphan*/  token_start; } ;
struct TYPE_3__ {int npath; int* array_cur_index; scalar_t__* path_indexes; TYPE_2__* lex; int /*<<< orphan*/  result_start; } ;
typedef  TYPE_1__ GetState ;

/* Variables and functions */
 scalar_t__ INT_MIN ; 
 int json_count_array_elements (TYPE_2__*) ; 

__attribute__((used)) static void
get_array_start(void *state)
{
	GetState   *_state = (GetState *) state;
	int			lex_level = _state->lex->lex_level;

	if (lex_level < _state->npath)
	{
		/* Initialize counting of elements in this array */
		_state->array_cur_index[lex_level] = -1;

		/* INT_MIN value is reserved to represent invalid subscript */
		if (_state->path_indexes[lex_level] < 0 &&
			_state->path_indexes[lex_level] != INT_MIN)
		{
			/* Negative subscript -- convert to positive-wise subscript */
			int			nelements = json_count_array_elements(_state->lex);

			if (-_state->path_indexes[lex_level] <= nelements)
				_state->path_indexes[lex_level] += nelements;
		}
	}
	else if (lex_level == 0 && _state->npath == 0)
	{
		/*
		 * Special case: we should match the entire array.  We only need this
		 * at the outermost level because at nested levels the match will have
		 * been started by the outer field or array element callback.
		 */
		_state->result_start = _state->lex->token_start;
	}
}