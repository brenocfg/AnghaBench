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
struct TYPE_9__ {int /*<<< orphan*/  ecxt_per_tuple_memory; } ;
struct TYPE_8__ {scalar_t__ key_toastable; int /*<<< orphan*/ * key_expr; TYPE_1__* scan_key; } ;
struct TYPE_7__ {int /*<<< orphan*/  sk_flags; void* sk_argument; } ;
typedef  TYPE_1__* ScanKey ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ IndexRuntimeKeyInfo ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_3__ ExprContext ;
typedef  void* Datum ;

/* Variables and functions */
 void* ExecEvalExpr (int /*<<< orphan*/ *,TYPE_3__*,int*) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_DETOAST_DATUM (void*) ; 
 void* PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SK_ISNULL ; 

void
ExecIndexEvalRuntimeKeys(ExprContext *econtext,
						 IndexRuntimeKeyInfo *runtimeKeys, int numRuntimeKeys)
{
	int			j;
	MemoryContext oldContext;

	/* We want to keep the key values in per-tuple memory */
	oldContext = MemoryContextSwitchTo(econtext->ecxt_per_tuple_memory);

	for (j = 0; j < numRuntimeKeys; j++)
	{
		ScanKey		scan_key = runtimeKeys[j].scan_key;
		ExprState  *key_expr = runtimeKeys[j].key_expr;
		Datum		scanvalue;
		bool		isNull;

		/*
		 * For each run-time key, extract the run-time expression and evaluate
		 * it with respect to the current context.  We then stick the result
		 * into the proper scan key.
		 *
		 * Note: the result of the eval could be a pass-by-ref value that's
		 * stored in some outer scan's tuple, not in
		 * econtext->ecxt_per_tuple_memory.  We assume that the outer tuple
		 * will stay put throughout our scan.  If this is wrong, we could copy
		 * the result into our context explicitly, but I think that's not
		 * necessary.
		 *
		 * It's also entirely possible that the result of the eval is a
		 * toasted value.  In this case we should forcibly detoast it, to
		 * avoid repeat detoastings each time the value is examined by an
		 * index support function.
		 */
		scanvalue = ExecEvalExpr(key_expr,
								 econtext,
								 &isNull);
		if (isNull)
		{
			scan_key->sk_argument = scanvalue;
			scan_key->sk_flags |= SK_ISNULL;
		}
		else
		{
			if (runtimeKeys[j].key_toastable)
				scanvalue = PointerGetDatum(PG_DETOAST_DATUM(scanvalue));
			scan_key->sk_argument = scanvalue;
			scan_key->sk_flags &= ~SK_ISNULL;
		}
	}

	MemoryContextSwitchTo(oldContext);
}