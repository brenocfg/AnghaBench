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
struct TYPE_4__ {scalar_t__ npath; int next_scalar; int /*<<< orphan*/ * tresult; TYPE_1__* lex; scalar_t__ normalize_results; } ;
struct TYPE_3__ {int lex_level; char* input; char* prev_token_terminator; } ;
typedef  scalar_t__ JsonTokenType ;
typedef  TYPE_2__ GetState ;

/* Variables and functions */
 scalar_t__ JSON_TOKEN_NULL ; 
 scalar_t__ JSON_TOKEN_STRING ; 
 int /*<<< orphan*/ * cstring_to_text (char*) ; 
 int /*<<< orphan*/ * cstring_to_text_with_len (char*,int) ; 

__attribute__((used)) static void
get_scalar(void *state, char *token, JsonTokenType tokentype)
{
	GetState   *_state = (GetState *) state;
	int			lex_level = _state->lex->lex_level;

	/* Check for whole-object match */
	if (lex_level == 0 && _state->npath == 0)
	{
		if (_state->normalize_results && tokentype == JSON_TOKEN_STRING)
		{
			/* we want the de-escaped string */
			_state->next_scalar = true;
		}
		else if (_state->normalize_results && tokentype == JSON_TOKEN_NULL)
		{
			_state->tresult = (text *) NULL;
		}
		else
		{
			/*
			 * This is a bit hokey: we will suppress whitespace after the
			 * scalar token, but not whitespace before it.  Probably not worth
			 * doing our own space-skipping to avoid that.
			 */
			char	   *start = _state->lex->input;
			int			len = _state->lex->prev_token_terminator - start;

			_state->tresult = cstring_to_text_with_len(start, len);
		}
	}

	if (_state->next_scalar)
	{
		/* a de-escaped text value is wanted, so supply it */
		_state->tresult = cstring_to_text(token);
		/* make sure the next call to get_scalar doesn't overwrite it */
		_state->next_scalar = false;
	}
}