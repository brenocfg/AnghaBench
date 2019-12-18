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
struct TYPE_5__ {char* data; int len; } ;
struct TYPE_4__ {int skip_next_null; TYPE_2__* strval; } ;
typedef  TYPE_1__ StripnullState ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfoCharMacro (TYPE_2__*,char) ; 
 int /*<<< orphan*/  escape_json (TYPE_2__*,char*) ; 

__attribute__((used)) static void
sn_object_field_start(void *state, char *fname, bool isnull)
{
	StripnullState *_state = (StripnullState *) state;

	if (isnull)
	{
		/*
		 * The next thing must be a scalar or isnull couldn't be true, so
		 * there is no danger of this state being carried down into a nested
		 * object or array. The flag will be reset in the scalar action.
		 */
		_state->skip_next_null = true;
		return;
	}

	if (_state->strval->data[_state->strval->len - 1] != '{')
		appendStringInfoCharMacro(_state->strval, ',');

	/*
	 * Unfortunately we don't have the quoted and escaped string any more, so
	 * we have to re-escape it.
	 */
	escape_json(_state->strval, fname);

	appendStringInfoCharMacro(_state->strval, ':');
}