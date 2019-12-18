#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  size; int /*<<< orphan*/  contVal; } ;
typedef  TYPE_1__ JsonbParseState ;

/* Variables and functions */
 void* palloc (int) ; 

__attribute__((used)) static JsonbParseState *
clone_parse_state(JsonbParseState *state)
{
	JsonbParseState *result,
			   *icursor,
			   *ocursor;

	if (state == NULL)
		return NULL;

	result = palloc(sizeof(JsonbParseState));
	icursor = state;
	ocursor = result;
	for (;;)
	{
		ocursor->contVal = icursor->contVal;
		ocursor->size = icursor->size;
		icursor = icursor->next;
		if (icursor == NULL)
			break;
		ocursor->next = palloc(sizeof(JsonbParseState));
		ocursor = ocursor->next;
	}
	ocursor->next = NULL;

	return result;
}