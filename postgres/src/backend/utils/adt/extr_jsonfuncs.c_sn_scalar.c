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
struct TYPE_2__ {int skip_next_null; int /*<<< orphan*/  strval; } ;
typedef  TYPE_1__ StripnullState ;
typedef  scalar_t__ JsonTokenType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ JSON_TOKEN_NULL ; 
 scalar_t__ JSON_TOKEN_STRING ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  escape_json (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
sn_scalar(void *state, char *token, JsonTokenType tokentype)
{
	StripnullState *_state = (StripnullState *) state;

	if (_state->skip_next_null)
	{
		Assert(tokentype == JSON_TOKEN_NULL);
		_state->skip_next_null = false;
		return;
	}

	if (tokentype == JSON_TOKEN_STRING)
		escape_json(_state->strval, token);
	else
		appendStringInfoString(_state->strval, token);
}