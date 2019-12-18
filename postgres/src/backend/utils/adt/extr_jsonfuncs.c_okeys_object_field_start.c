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
struct TYPE_4__ {int result_count; int result_size; char** result; TYPE_1__* lex; } ;
struct TYPE_3__ {int lex_level; } ;
typedef  TYPE_2__ OkeysState ;

/* Variables and functions */
 char* pstrdup (char*) ; 
 scalar_t__ repalloc (char**,int) ; 

__attribute__((used)) static void
okeys_object_field_start(void *state, char *fname, bool isnull)
{
	OkeysState *_state = (OkeysState *) state;

	/* only collecting keys for the top level object */
	if (_state->lex->lex_level != 1)
		return;

	/* enlarge result array if necessary */
	if (_state->result_count >= _state->result_size)
	{
		_state->result_size *= 2;
		_state->result = (char **)
			repalloc(_state->result, sizeof(char *) * _state->result_size);
	}

	/* save a copy of the field name */
	_state->result[_state->result_count++] = pstrdup(fname);
}