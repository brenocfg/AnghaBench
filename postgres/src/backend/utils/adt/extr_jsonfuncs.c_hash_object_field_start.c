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
struct TYPE_4__ {scalar_t__ saved_token_type; int /*<<< orphan*/ * save_json_start; TYPE_1__* lex; } ;
struct TYPE_3__ {int lex_level; scalar_t__ token_type; int /*<<< orphan*/ * token_start; } ;
typedef  TYPE_2__ JHashState ;

/* Variables and functions */
 scalar_t__ JSON_TOKEN_ARRAY_START ; 
 scalar_t__ JSON_TOKEN_OBJECT_START ; 

__attribute__((used)) static void
hash_object_field_start(void *state, char *fname, bool isnull)
{
	JHashState *_state = (JHashState *) state;

	if (_state->lex->lex_level > 1)
		return;

	/* remember token type */
	_state->saved_token_type = _state->lex->token_type;

	if (_state->lex->token_type == JSON_TOKEN_ARRAY_START ||
		_state->lex->token_type == JSON_TOKEN_OBJECT_START)
	{
		/* remember start position of the whole text of the subobject */
		_state->save_json_start = _state->lex->token_start;
	}
	else
	{
		/* must be a scalar */
		_state->save_json_start = NULL;
	}
}