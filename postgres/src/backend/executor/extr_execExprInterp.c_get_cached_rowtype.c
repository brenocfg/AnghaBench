#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_7__ {scalar_t__ tdtypeid; scalar_t__ tdtypmod; } ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ExprContext ;

/* Variables and functions */
 int /*<<< orphan*/  PointerGetDatum (TYPE_1__**) ; 
 int /*<<< orphan*/  RegisterExprContextCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTupleDesc (TYPE_1__*) ; 
 int /*<<< orphan*/  ShutdownTupleDescRef ; 
 TYPE_1__* lookup_rowtype_tupdesc (scalar_t__,scalar_t__) ; 

__attribute__((used)) static TupleDesc
get_cached_rowtype(Oid type_id, int32 typmod,
				   TupleDesc *cache_field, ExprContext *econtext)
{
	TupleDesc	tupDesc = *cache_field;

	/* Do lookup if no cached value or if requested type changed */
	if (tupDesc == NULL ||
		type_id != tupDesc->tdtypeid ||
		typmod != tupDesc->tdtypmod)
	{
		tupDesc = lookup_rowtype_tupdesc(type_id, typmod);

		if (*cache_field)
		{
			/* Release old tupdesc; but callback is already registered */
			ReleaseTupleDesc(*cache_field);
		}
		else
		{
			/* Need to register shutdown callback to release tupdesc */
			RegisterExprContextCallback(econtext,
										ShutdownTupleDescRef,
										PointerGetDatum(cache_field));
		}
		*cache_field = tupDesc;
	}
	return tupDesc;
}