#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  text ;
struct TYPE_5__ {int /*<<< orphan*/  flags; void* action_state; int /*<<< orphan*/  action; int /*<<< orphan*/ * lex; } ;
struct TYPE_4__ {int /*<<< orphan*/  object_field_start; int /*<<< orphan*/  scalar; void* semstate; } ;
typedef  TYPE_1__ JsonSemAction ;
typedef  int /*<<< orphan*/  JsonLexContext ;
typedef  int /*<<< orphan*/  JsonIterateStringValuesAction ;
typedef  TYPE_2__ IterateJsonStringValuesState ;

/* Variables and functions */
 int /*<<< orphan*/  iterate_values_object_field_start ; 
 int /*<<< orphan*/  iterate_values_scalar ; 
 int /*<<< orphan*/ * makeJsonLexContext (int /*<<< orphan*/ *,int) ; 
 void* palloc0 (int) ; 
 int /*<<< orphan*/  pg_parse_json (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
iterate_json_values(text *json, uint32 flags, void *action_state,
					JsonIterateStringValuesAction action)
{
	JsonLexContext *lex = makeJsonLexContext(json, true);
	JsonSemAction *sem = palloc0(sizeof(JsonSemAction));
	IterateJsonStringValuesState *state = palloc0(sizeof(IterateJsonStringValuesState));

	state->lex = lex;
	state->action = action;
	state->action_state = action_state;
	state->flags = flags;

	sem->semstate = (void *) state;
	sem->scalar = iterate_values_scalar;
	sem->object_field_start = iterate_values_object_field_start;

	pg_parse_json(lex, sem);
}