#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_30__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_31__ {TYPE_4__ binary; } ;
struct TYPE_35__ {TYPE_5__ val; int /*<<< orphan*/  type; } ;
struct TYPE_26__ {int /*<<< orphan*/  base_typmod; int /*<<< orphan*/  base_typid; } ;
struct TYPE_32__ {TYPE_14__ composite; } ;
struct TYPE_33__ {TYPE_6__ io; } ;
struct TYPE_34__ {scalar_t__ argtype; TYPE_7__ c; int /*<<< orphan*/  fn_mcxt; } ;
struct TYPE_28__ {int /*<<< orphan*/  type; int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
struct TYPE_29__ {TYPE_9__* jsonb; TYPE_2__ json; } ;
struct TYPE_27__ {TYPE_8__* fn_extra; int /*<<< orphan*/  fn_mcxt; } ;
struct TYPE_25__ {TYPE_1__* flinfo; } ;
struct TYPE_24__ {int is_json; TYPE_3__ val; int /*<<< orphan*/  member_0; } ;
struct TYPE_23__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_8__ PopulateRecordCache ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_9__ JsonbValue ;
typedef  TYPE_10__ Jsonb ;
typedef  TYPE_11__ JsValue ;
typedef  int /*<<< orphan*/ * HeapTupleHeader ;
typedef  TYPE_12__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypMod (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypeId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JSON_TOKEN_INVALID ; 
 TYPE_8__* MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PG_ARGISNULL (int) ; 
 int /*<<< orphan*/ * PG_GETARG_HEAPTUPLEHEADER (int /*<<< orphan*/ ) ; 
 TYPE_10__* PG_GETARG_JSONB_P (int) ; 
 int /*<<< orphan*/ * PG_GETARG_TEXT_PP (int) ; 
 int /*<<< orphan*/  PG_RETURN_DATUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_NULL () ; 
 int /*<<< orphan*/  PG_RETURN_POINTER (int /*<<< orphan*/ *) ; 
 scalar_t__ RECORDOID ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ VARSIZE (TYPE_10__*) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_record_type_from_argument (TYPE_12__*,char const*,TYPE_8__*) ; 
 int /*<<< orphan*/  get_record_type_from_query (TYPE_12__*,char const*,TYPE_8__*) ; 
 int /*<<< orphan*/  jbvBinary ; 
 int /*<<< orphan*/  populate_composite (TYPE_14__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_11__*,int) ; 

__attribute__((used)) static Datum
populate_record_worker(FunctionCallInfo fcinfo, const char *funcname,
					   bool is_json, bool have_record_arg)
{
	int			json_arg_num = have_record_arg ? 1 : 0;
	JsValue		jsv = {0};
	HeapTupleHeader rec;
	Datum		rettuple;
	JsonbValue	jbv;
	MemoryContext fnmcxt = fcinfo->flinfo->fn_mcxt;
	PopulateRecordCache *cache = fcinfo->flinfo->fn_extra;

	/*
	 * If first time through, identify input/result record type.  Note that
	 * this stanza looks only at fcinfo context, which can't change during the
	 * query; so we may not be able to fully resolve a RECORD input type yet.
	 */
	if (!cache)
	{
		fcinfo->flinfo->fn_extra = cache =
			MemoryContextAllocZero(fnmcxt, sizeof(*cache));
		cache->fn_mcxt = fnmcxt;

		if (have_record_arg)
			get_record_type_from_argument(fcinfo, funcname, cache);
		else
			get_record_type_from_query(fcinfo, funcname, cache);
	}

	/* Collect record arg if we have one */
	if (!have_record_arg)
		rec = NULL;				/* it's json{b}_to_record() */
	else if (!PG_ARGISNULL(0))
	{
		rec = PG_GETARG_HEAPTUPLEHEADER(0);

		/*
		 * When declared arg type is RECORD, identify actual record type from
		 * the tuple itself.
		 */
		if (cache->argtype == RECORDOID)
		{
			cache->c.io.composite.base_typid = HeapTupleHeaderGetTypeId(rec);
			cache->c.io.composite.base_typmod = HeapTupleHeaderGetTypMod(rec);
		}
	}
	else
	{
		rec = NULL;

		/*
		 * When declared arg type is RECORD, identify actual record type from
		 * calling query, or fail if we can't.
		 */
		if (cache->argtype == RECORDOID)
		{
			get_record_type_from_query(fcinfo, funcname, cache);
			/* This can't change argtype, which is important for next time */
			Assert(cache->argtype == RECORDOID);
		}
	}

	/* If no JSON argument, just return the record (if any) unchanged */
	if (PG_ARGISNULL(json_arg_num))
	{
		if (rec)
			PG_RETURN_POINTER(rec);
		else
			PG_RETURN_NULL();
	}

	jsv.is_json = is_json;

	if (is_json)
	{
		text	   *json = PG_GETARG_TEXT_PP(json_arg_num);

		jsv.val.json.str = VARDATA_ANY(json);
		jsv.val.json.len = VARSIZE_ANY_EXHDR(json);
		jsv.val.json.type = JSON_TOKEN_INVALID; /* not used in
												 * populate_composite() */
	}
	else
	{
		Jsonb	   *jb = PG_GETARG_JSONB_P(json_arg_num);

		jsv.val.jsonb = &jbv;

		/* fill binary jsonb value pointing to jb */
		jbv.type = jbvBinary;
		jbv.val.binary.data = &jb->root;
		jbv.val.binary.len = VARSIZE(jb) - VARHDRSZ;
	}

	rettuple = populate_composite(&cache->c.io.composite, cache->argtype,
								  NULL, fnmcxt, rec, &jsv, false);

	PG_RETURN_DATUM(rettuple);
}