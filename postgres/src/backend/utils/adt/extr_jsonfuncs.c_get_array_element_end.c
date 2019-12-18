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
typedef  int /*<<< orphan*/  text ;
struct TYPE_4__ {int npath; int* pathok; scalar_t__* path_indexes; scalar_t__* array_cur_index; char* result_start; int /*<<< orphan*/ * tresult; TYPE_1__* lex; scalar_t__ normalize_results; } ;
struct TYPE_3__ {int lex_level; char* prev_token_terminator; } ;
typedef  TYPE_2__ GetState ;

/* Variables and functions */
 int /*<<< orphan*/ * cstring_to_text_with_len (char*,int) ; 

__attribute__((used)) static void
get_array_element_end(void *state, bool isnull)
{
	GetState   *_state = (GetState *) state;
	bool		get_last = false;
	int			lex_level = _state->lex->lex_level;

	/* same tests as in get_array_element_start */
	if (lex_level <= _state->npath &&
		_state->pathok[lex_level - 1] &&
		_state->path_indexes != NULL &&
		_state->array_cur_index[lex_level - 1] == _state->path_indexes[lex_level - 1])
	{
		if (lex_level < _state->npath)
		{
			/* done with this element so reset pathok */
			_state->pathok[lex_level] = false;
		}
		else
		{
			/* end of path, so we want this value */
			get_last = true;
		}
	}

	/* same logic as for objects */
	if (get_last && _state->result_start != NULL)
	{
		if (isnull && _state->normalize_results)
			_state->tresult = (text *) NULL;
		else
		{
			char	   *start = _state->result_start;
			int			len = _state->lex->prev_token_terminator - start;

			_state->tresult = cstring_to_text_with_len(start, len);
		}

		_state->result_start = NULL;
	}
}