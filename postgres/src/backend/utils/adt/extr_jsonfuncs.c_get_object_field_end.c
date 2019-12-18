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
struct TYPE_4__ {int npath; int* pathok; char* result_start; int /*<<< orphan*/ * tresult; TYPE_1__* lex; scalar_t__ normalize_results; int /*<<< orphan*/ ** path_names; } ;
struct TYPE_3__ {int lex_level; char* prev_token_terminator; } ;
typedef  TYPE_2__ GetState ;

/* Variables and functions */
 int /*<<< orphan*/ * cstring_to_text_with_len (char*,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
get_object_field_end(void *state, char *fname, bool isnull)
{
	GetState   *_state = (GetState *) state;
	bool		get_last = false;
	int			lex_level = _state->lex->lex_level;

	/* same tests as in get_object_field_start */
	if (lex_level <= _state->npath &&
		_state->pathok[lex_level - 1] &&
		_state->path_names != NULL &&
		_state->path_names[lex_level - 1] != NULL &&
		strcmp(fname, _state->path_names[lex_level - 1]) == 0)
	{
		if (lex_level < _state->npath)
		{
			/* done with this field so reset pathok */
			_state->pathok[lex_level] = false;
		}
		else
		{
			/* end of path, so we want this value */
			get_last = true;
		}
	}

	/* for as_text scalar case, our work is already done */
	if (get_last && _state->result_start != NULL)
	{
		/*
		 * make a text object from the string from the previously noted json
		 * start up to the end of the previous token (the lexer is by now
		 * ahead of us on whatever came after what we're interested in).
		 */
		if (isnull && _state->normalize_results)
			_state->tresult = (text *) NULL;
		else
		{
			char	   *start = _state->result_start;
			int			len = _state->lex->prev_token_terminator - start;

			_state->tresult = cstring_to_text_with_len(start, len);
		}

		/* this should be unnecessary but let's do it for cleanliness: */
		_state->result_start = NULL;
	}
}