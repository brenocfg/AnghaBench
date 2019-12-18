#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct varlena {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  atomic; } ;
struct TYPE_8__ {scalar_t__ dtype; int freeval; int isnull; int /*<<< orphan*/  promise; int /*<<< orphan*/  value; TYPE_1__* datatype; } ;
struct TYPE_7__ {int typlen; } ;
typedef  TYPE_2__ PLpgSQL_var ;
typedef  TYPE_3__ PLpgSQL_execstate ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumIsReadWriteExpandedObject (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DeleteExpandedObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ PLPGSQL_DTYPE_PROMISE ; 
 scalar_t__ PLPGSQL_DTYPE_VAR ; 
 int /*<<< orphan*/  PLPGSQL_PROMISE_NONE ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ VARATT_IS_EXTERNAL_NON_EXPANDED (scalar_t__) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  detoast_external_attr (struct varlena*) ; 
 int /*<<< orphan*/  get_eval_mcontext (TYPE_3__*) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 

__attribute__((used)) static void
assign_simple_var(PLpgSQL_execstate *estate, PLpgSQL_var *var,
				  Datum newvalue, bool isnull, bool freeable)
{
	Assert(var->dtype == PLPGSQL_DTYPE_VAR ||
		   var->dtype == PLPGSQL_DTYPE_PROMISE);

	/*
	 * In non-atomic contexts, we do not want to store TOAST pointers in
	 * variables, because such pointers might become stale after a commit.
	 * Forcibly detoast in such cases.  We don't want to detoast (flatten)
	 * expanded objects, however; those should be OK across a transaction
	 * boundary since they're just memory-resident objects.  (Elsewhere in
	 * this module, operations on expanded records likewise need to request
	 * detoasting of record fields when !estate->atomic.  Expanded arrays are
	 * not a problem since all array entries are always detoasted.)
	 */
	if (!estate->atomic && !isnull && var->datatype->typlen == -1 &&
		VARATT_IS_EXTERNAL_NON_EXPANDED(DatumGetPointer(newvalue)))
	{
		MemoryContext oldcxt;
		Datum		detoasted;

		/*
		 * Do the detoasting in the eval_mcontext to avoid long-term leakage
		 * of whatever memory toast fetching might leak.  Then we have to copy
		 * the detoasted datum to the function's main context, which is a
		 * pain, but there's little choice.
		 */
		oldcxt = MemoryContextSwitchTo(get_eval_mcontext(estate));
		detoasted = PointerGetDatum(detoast_external_attr((struct varlena *) DatumGetPointer(newvalue)));
		MemoryContextSwitchTo(oldcxt);
		/* Now's a good time to not leak the input value if it's freeable */
		if (freeable)
			pfree(DatumGetPointer(newvalue));
		/* Once we copy the value, it's definitely freeable */
		newvalue = datumCopy(detoasted, false, -1);
		freeable = true;
		/* Can't clean up eval_mcontext here, but it'll happen before long */
	}

	/* Free the old value if needed */
	if (var->freeval)
	{
		if (DatumIsReadWriteExpandedObject(var->value,
										   var->isnull,
										   var->datatype->typlen))
			DeleteExpandedObject(var->value);
		else
			pfree(DatumGetPointer(var->value));
	}
	/* Assign new value to datum */
	var->value = newvalue;
	var->isnull = isnull;
	var->freeval = freeable;

	/*
	 * If it's a promise variable, then either we just assigned the promised
	 * value, or the user explicitly assigned an overriding value.  Either
	 * way, cancel the promise.
	 */
	var->promise = PLPGSQL_PROMISE_NONE;
}