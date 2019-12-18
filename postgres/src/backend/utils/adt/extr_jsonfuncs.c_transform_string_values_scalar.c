#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_2__ {int /*<<< orphan*/  strval; int /*<<< orphan*/  action_state; int /*<<< orphan*/ * (* action ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ TransformJsonStringValuesState ;
typedef  scalar_t__ JsonTokenType ;

/* Variables and functions */
 scalar_t__ JSON_TOKEN_STRING ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  escape_json (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
transform_string_values_scalar(void *state, char *token, JsonTokenType tokentype)
{
	TransformJsonStringValuesState *_state = (TransformJsonStringValuesState *) state;

	if (tokentype == JSON_TOKEN_STRING)
	{
		text	   *out = _state->action(_state->action_state, token, strlen(token));

		escape_json(_state->strval, text_to_cstring(out));
	}
	else
		appendStringInfoString(_state->strval, token);
}