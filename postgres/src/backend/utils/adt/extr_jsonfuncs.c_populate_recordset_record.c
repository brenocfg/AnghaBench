#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  domain_info; int /*<<< orphan*/  record_io; int /*<<< orphan*/  tupdesc; } ;
struct TYPE_13__ {int /*<<< orphan*/  t_data; int /*<<< orphan*/  t_tableOid; int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_len; } ;
struct TYPE_9__ {TYPE_6__ composite; } ;
struct TYPE_10__ {scalar_t__ typcat; TYPE_1__ io; } ;
struct TYPE_12__ {int /*<<< orphan*/  fn_mcxt; TYPE_2__ c; int /*<<< orphan*/  argtype; } ;
struct TYPE_11__ {int /*<<< orphan*/  tuple_store; int /*<<< orphan*/  rec; TYPE_4__* cache; } ;
typedef  TYPE_3__ PopulateRecordsetState ;
typedef  TYPE_4__ PopulateRecordCache ;
typedef  int /*<<< orphan*/  JsObject ;
typedef  int /*<<< orphan*/  HeapTupleHeader ;
typedef  TYPE_5__ HeapTupleData ;

/* Variables and functions */
 int /*<<< orphan*/  HeapTupleHeaderGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetDatumLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ItemPointerSetInvalid (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPECAT_COMPOSITE_DOMAIN ; 
 int /*<<< orphan*/  domain_check (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  populate_record (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tuplestore_puttuple (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  update_cached_tupdesc (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
populate_recordset_record(PopulateRecordsetState *state, JsObject *obj)
{
	PopulateRecordCache *cache = state->cache;
	HeapTupleHeader tuphead;
	HeapTupleData tuple;

	/* acquire/update cached tuple descriptor */
	update_cached_tupdesc(&cache->c.io.composite, cache->fn_mcxt);

	/* replace record fields from json */
	tuphead = populate_record(cache->c.io.composite.tupdesc,
							  &cache->c.io.composite.record_io,
							  state->rec,
							  cache->fn_mcxt,
							  obj);

	/* if it's domain over composite, check domain constraints */
	if (cache->c.typcat == TYPECAT_COMPOSITE_DOMAIN)
		domain_check(HeapTupleHeaderGetDatum(tuphead), false,
					 cache->argtype,
					 &cache->c.io.composite.domain_info,
					 cache->fn_mcxt);

	/* ok, save into tuplestore */
	tuple.t_len = HeapTupleHeaderGetDatumLength(tuphead);
	ItemPointerSetInvalid(&(tuple.t_self));
	tuple.t_tableOid = InvalidOid;
	tuple.t_data = tuphead;

	tuplestore_puttuple(state->tuple_store, &tuple);
}