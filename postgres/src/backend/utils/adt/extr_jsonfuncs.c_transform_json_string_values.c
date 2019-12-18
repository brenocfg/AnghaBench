#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_5__ {TYPE_4__* strval; void* action_state; int /*<<< orphan*/  action; int /*<<< orphan*/ * lex; } ;
typedef  TYPE_1__ TransformJsonStringValuesState ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  object_field_start; int /*<<< orphan*/  array_element_start; void* scalar; int /*<<< orphan*/  array_end; int /*<<< orphan*/  array_start; int /*<<< orphan*/  object_end; int /*<<< orphan*/  object_start; void* semstate; } ;
typedef  int /*<<< orphan*/  JsonTransformStringValuesAction ;
typedef  TYPE_2__ JsonSemAction ;
typedef  int /*<<< orphan*/  JsonLexContext ;

/* Variables and functions */
 int /*<<< orphan*/ * cstring_to_text_with_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeJsonLexContext (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* makeStringInfo () ; 
 void* palloc0 (int) ; 
 int /*<<< orphan*/  pg_parse_json (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  transform_string_values_array_element_start ; 
 int /*<<< orphan*/  transform_string_values_array_end ; 
 int /*<<< orphan*/  transform_string_values_array_start ; 
 int /*<<< orphan*/  transform_string_values_object_end ; 
 int /*<<< orphan*/  transform_string_values_object_field_start ; 
 int /*<<< orphan*/  transform_string_values_object_start ; 
 void* transform_string_values_scalar ; 

text *
transform_json_string_values(text *json, void *action_state,
							 JsonTransformStringValuesAction transform_action)
{
	JsonLexContext *lex = makeJsonLexContext(json, true);
	JsonSemAction *sem = palloc0(sizeof(JsonSemAction));
	TransformJsonStringValuesState *state = palloc0(sizeof(TransformJsonStringValuesState));

	state->lex = lex;
	state->strval = makeStringInfo();
	state->action = transform_action;
	state->action_state = action_state;

	sem->semstate = (void *) state;
	sem->scalar = transform_string_values_scalar;
	sem->object_start = transform_string_values_object_start;
	sem->object_end = transform_string_values_object_end;
	sem->array_start = transform_string_values_array_start;
	sem->array_end = transform_string_values_array_end;
	sem->scalar = transform_string_values_scalar;
	sem->array_element_start = transform_string_values_array_element_start;
	sem->object_field_start = transform_string_values_object_field_start;

	pg_parse_json(lex, sem);

	return cstring_to_text_with_len(state->strval->data, state->strval->len);
}