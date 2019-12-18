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
struct TYPE_4__ {int next_scalar; char* normalized_scalar; int result_start; int /*<<< orphan*/  tmp_cxt; int /*<<< orphan*/  tuple_store; int /*<<< orphan*/  ret_tdesc; TYPE_1__* lex; scalar_t__ normalize_results; } ;
struct TYPE_3__ {int lex_level; int prev_token_terminator; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__ EachState ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 scalar_t__ CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cstring_to_text_with_len (int,int) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  tuplestore_puttuple (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
each_object_field_end(void *state, char *fname, bool isnull)
{
	EachState  *_state = (EachState *) state;
	MemoryContext old_cxt;
	int			len;
	text	   *val;
	HeapTuple	tuple;
	Datum		values[2];
	bool		nulls[2] = {false, false};

	/* skip over nested objects */
	if (_state->lex->lex_level != 1)
		return;

	/* use the tmp context so we can clean up after each tuple is done */
	old_cxt = MemoryContextSwitchTo(_state->tmp_cxt);

	values[0] = CStringGetTextDatum(fname);

	if (isnull && _state->normalize_results)
	{
		nulls[1] = true;
		values[1] = (Datum) 0;
	}
	else if (_state->next_scalar)
	{
		values[1] = CStringGetTextDatum(_state->normalized_scalar);
		_state->next_scalar = false;
	}
	else
	{
		len = _state->lex->prev_token_terminator - _state->result_start;
		val = cstring_to_text_with_len(_state->result_start, len);
		values[1] = PointerGetDatum(val);
	}

	tuple = heap_form_tuple(_state->ret_tdesc, values, nulls);

	tuplestore_puttuple(_state->tuple_store, tuple);

	/* clean up and switch back */
	MemoryContextSwitchTo(old_cxt);
	MemoryContextReset(_state->tmp_cxt);
}