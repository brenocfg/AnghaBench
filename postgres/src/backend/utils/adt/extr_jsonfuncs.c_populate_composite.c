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
struct TYPE_4__ {int /*<<< orphan*/  domain_info; int /*<<< orphan*/  base_typid; int /*<<< orphan*/  record_io; int /*<<< orphan*/  tupdesc; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  JsValue ;
typedef  int /*<<< orphan*/  JsObject ;
typedef  int /*<<< orphan*/  HeapTupleHeader ;
typedef  scalar_t__ Datum ;
typedef  TYPE_1__ CompositeIOData ;

/* Variables and functions */
 scalar_t__ HeapTupleHeaderGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JsObjectFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsValueToJsObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECORDOID ; 
 int /*<<< orphan*/  domain_check (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  populate_record (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_cached_tupdesc (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
populate_composite(CompositeIOData *io,
				   Oid typid,
				   const char *colname,
				   MemoryContext mcxt,
				   HeapTupleHeader defaultval,
				   JsValue *jsv,
				   bool isnull)
{
	Datum		result;

	/* acquire/update cached tuple descriptor */
	update_cached_tupdesc(io, mcxt);

	if (isnull)
		result = (Datum) 0;
	else
	{
		HeapTupleHeader tuple;
		JsObject	jso;

		/* prepare input value */
		JsValueToJsObject(jsv, &jso);

		/* populate resulting record tuple */
		tuple = populate_record(io->tupdesc, &io->record_io,
								defaultval, mcxt, &jso);
		result = HeapTupleHeaderGetDatum(tuple);

		JsObjectFree(&jso);
	}

	/*
	 * If it's domain over composite, check domain constraints.  (This should
	 * probably get refactored so that we can see the TYPECAT value, but for
	 * now, we can tell by comparing typid to base_typid.)
	 */
	if (typid != io->base_typid && typid != RECORDOID)
		domain_check(result, isnull, typid, &io->domain_info, mcxt);

	return result;
}