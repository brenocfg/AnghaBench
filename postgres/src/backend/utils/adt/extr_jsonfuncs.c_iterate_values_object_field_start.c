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
typedef  TYPE_1__ IterateJsonStringValuesState ;

/* Variables and functions */
 int jtiKey ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iterate_values_object_field_start(void *state, char *fname, bool isnull)
{
	IterateJsonStringValuesState *_state = (IterateJsonStringValuesState *) state;

	if (_state->flags & jtiKey)
	{
		char	   *val = pstrdup(fname);

		_state->action(_state->action_state, val, strlen(val));
	}
}