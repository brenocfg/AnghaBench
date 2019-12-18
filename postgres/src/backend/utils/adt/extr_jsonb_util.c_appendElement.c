#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ nElems; TYPE_3__* elems; } ;
struct TYPE_10__ {TYPE_1__ array; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_2__ val; } ;
struct TYPE_12__ {int size; TYPE_3__ contVal; } ;
typedef  TYPE_3__ JsonbValue ;
typedef  TYPE_4__ JsonbParseState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ JSONB_MAX_ELEMS ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__) ; 
 scalar_t__ jbvArray ; 
 TYPE_3__* repalloc (TYPE_3__*,int) ; 

__attribute__((used)) static void
appendElement(JsonbParseState *pstate, JsonbValue *scalarVal)
{
	JsonbValue *array = &pstate->contVal;

	Assert(array->type == jbvArray);

	if (array->val.array.nElems >= JSONB_MAX_ELEMS)
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("number of jsonb array elements exceeds the maximum allowed (%zu)",
						JSONB_MAX_ELEMS)));

	if (array->val.array.nElems >= pstate->size)
	{
		pstate->size *= 2;
		array->val.array.elems = repalloc(array->val.array.elems,
										  sizeof(JsonbValue) * pstate->size);
	}

	array->val.array.elems[array->val.array.nElems++] = *scalarVal;
}