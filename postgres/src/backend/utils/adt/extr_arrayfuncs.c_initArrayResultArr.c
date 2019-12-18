#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int private_cxt; void* element_type; void* array_type; int /*<<< orphan*/  mcontext; } ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ ArrayBuildStateArr ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OidIsValid (void*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (void*) ; 
 void* get_element_type (void*) ; 

ArrayBuildStateArr *
initArrayResultArr(Oid array_type, Oid element_type, MemoryContext rcontext,
				   bool subcontext)
{
	ArrayBuildStateArr *astate;
	MemoryContext arr_context = rcontext;	/* by default use the parent ctx */

	/* Lookup element type, unless element_type already provided */
	if (!OidIsValid(element_type))
	{
		element_type = get_element_type(array_type);

		if (!OidIsValid(element_type))
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("data type %s is not an array type",
							format_type_be(array_type))));
	}

	/* Make a temporary context to hold all the junk */
	if (subcontext)
		arr_context = AllocSetContextCreate(rcontext,
											"accumArrayResultArr",
											ALLOCSET_DEFAULT_SIZES);

	/* Note we initialize all fields to zero */
	astate = (ArrayBuildStateArr *)
		MemoryContextAllocZero(arr_context, sizeof(ArrayBuildStateArr));
	astate->mcontext = arr_context;
	astate->private_cxt = subcontext;

	/* Save relevant datatype information */
	astate->array_type = array_type;
	astate->element_type = element_type;

	return astate;
}