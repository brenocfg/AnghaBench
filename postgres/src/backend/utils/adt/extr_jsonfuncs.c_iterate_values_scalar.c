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
struct TYPE_2__ {int flags; int /*<<< orphan*/  action_state; int /*<<< orphan*/  (* action ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
typedef  int JsonTokenType ;
typedef  TYPE_1__ IterateJsonStringValuesState ;

/* Variables and functions */
#define  JSON_TOKEN_FALSE 131 
#define  JSON_TOKEN_NUMBER 130 
#define  JSON_TOKEN_STRING 129 
#define  JSON_TOKEN_TRUE 128 
 int jtiBool ; 
 int jtiNumeric ; 
 int jtiString ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iterate_values_scalar(void *state, char *token, JsonTokenType tokentype)
{
	IterateJsonStringValuesState *_state = (IterateJsonStringValuesState *) state;

	switch (tokentype)
	{
		case JSON_TOKEN_STRING:
			if (_state->flags & jtiString)
				_state->action(_state->action_state, token, strlen(token));
			break;
		case JSON_TOKEN_NUMBER:
			if (_state->flags & jtiNumeric)
				_state->action(_state->action_state, token, strlen(token));
			break;
		case JSON_TOKEN_TRUE:
		case JSON_TOKEN_FALSE:
			if (_state->flags & jtiBool)
				_state->action(_state->action_state, token, strlen(token));
			break;
		default:
			/* do not call callback for any other token */
			break;
	}
}