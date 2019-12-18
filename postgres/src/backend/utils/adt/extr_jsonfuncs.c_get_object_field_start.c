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
struct TYPE_4__ {int npath; int* pathok; int next_scalar; TYPE_1__* lex; int /*<<< orphan*/ * result_start; scalar_t__ normalize_results; int /*<<< orphan*/ * tresult; int /*<<< orphan*/ ** path_names; } ;
struct TYPE_3__ {int lex_level; scalar_t__ token_type; int /*<<< orphan*/ * token_start; } ;
typedef  TYPE_2__ GetState ;

/* Variables and functions */
 scalar_t__ JSON_TOKEN_STRING ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
get_object_field_start(void *state, char *fname, bool isnull)
{
	GetState   *_state = (GetState *) state;
	bool		get_next = false;
	int			lex_level = _state->lex->lex_level;

	if (lex_level <= _state->npath &&
		_state->pathok[lex_level - 1] &&
		_state->path_names != NULL &&
		_state->path_names[lex_level - 1] != NULL &&
		strcmp(fname, _state->path_names[lex_level - 1]) == 0)
	{
		if (lex_level < _state->npath)
		{
			/* if not at end of path just mark path ok */
			_state->pathok[lex_level] = true;
		}
		else
		{
			/* end of path, so we want this value */
			get_next = true;
		}
	}

	if (get_next)
	{
		/* this object overrides any previous matching object */
		_state->tresult = NULL;
		_state->result_start = NULL;

		if (_state->normalize_results &&
			_state->lex->token_type == JSON_TOKEN_STRING)
		{
			/* for as_text variants, tell get_scalar to set it for us */
			_state->next_scalar = true;
		}
		else
		{
			/* for non-as_text variants, just note the json starting point */
			_state->result_start = _state->lex->token_start;
		}
	}
}