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
struct TYPE_2__ {int /*<<< orphan*/  strval; } ;
typedef  TYPE_1__ TransformJsonStringValuesState ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfoCharMacro (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void
transform_string_values_object_end(void *state)
{
	TransformJsonStringValuesState *_state = (TransformJsonStringValuesState *) state;

	appendStringInfoCharMacro(_state->strval, '}');
}