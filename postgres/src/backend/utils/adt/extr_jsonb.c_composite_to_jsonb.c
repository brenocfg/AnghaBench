#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  TYPE_3__* TupleDesc ;
struct TYPE_23__ {int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attname; scalar_t__ attisdropped; } ;
struct TYPE_22__ {int /*<<< orphan*/  t_data; int /*<<< orphan*/  t_len; } ;
struct TYPE_21__ {int /*<<< orphan*/  parseState; void* res; } ;
struct TYPE_17__ {char* val; int /*<<< orphan*/  len; } ;
struct TYPE_18__ {TYPE_1__ string; } ;
struct TYPE_20__ {TYPE_2__ val; int /*<<< orphan*/  type; } ;
struct TYPE_19__ {int natts; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbTypeCategory ;
typedef  TYPE_5__ JsonbInState ;
typedef  int /*<<< orphan*/  HeapTupleHeader ;
typedef  TYPE_6__ HeapTupleData ;
typedef  TYPE_7__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetHeapTupleHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetDatumLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypMod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleHeaderGetTypeId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  JSONBTYPE_NULL ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseTupleDesc (TYPE_3__*) ; 
 TYPE_7__* TupleDescAttr (TYPE_3__*,int) ; 
 int /*<<< orphan*/  WJB_BEGIN_OBJECT ; 
 int /*<<< orphan*/  WJB_END_OBJECT ; 
 int /*<<< orphan*/  WJB_KEY ; 
 int /*<<< orphan*/  datum_to_jsonb (int /*<<< orphan*/ ,int,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  heap_getattr (TYPE_6__*,int,TYPE_3__*,int*) ; 
 int /*<<< orphan*/  jbvString ; 
 int /*<<< orphan*/  jsonb_categorize_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* lookup_rowtype_tupdesc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* pushJsonbValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
composite_to_jsonb(Datum composite, JsonbInState *result)
{
	HeapTupleHeader td;
	Oid			tupType;
	int32		tupTypmod;
	TupleDesc	tupdesc;
	HeapTupleData tmptup,
			   *tuple;
	int			i;

	td = DatumGetHeapTupleHeader(composite);

	/* Extract rowtype info and find a tupdesc */
	tupType = HeapTupleHeaderGetTypeId(td);
	tupTypmod = HeapTupleHeaderGetTypMod(td);
	tupdesc = lookup_rowtype_tupdesc(tupType, tupTypmod);

	/* Build a temporary HeapTuple control structure */
	tmptup.t_len = HeapTupleHeaderGetDatumLength(td);
	tmptup.t_data = td;
	tuple = &tmptup;

	result->res = pushJsonbValue(&result->parseState, WJB_BEGIN_OBJECT, NULL);

	for (i = 0; i < tupdesc->natts; i++)
	{
		Datum		val;
		bool		isnull;
		char	   *attname;
		JsonbTypeCategory tcategory;
		Oid			outfuncoid;
		JsonbValue	v;
		Form_pg_attribute att = TupleDescAttr(tupdesc, i);

		if (att->attisdropped)
			continue;

		attname = NameStr(att->attname);

		v.type = jbvString;
		/* don't need checkStringLen here - can't exceed maximum name length */
		v.val.string.len = strlen(attname);
		v.val.string.val = attname;

		result->res = pushJsonbValue(&result->parseState, WJB_KEY, &v);

		val = heap_getattr(tuple, i + 1, tupdesc, &isnull);

		if (isnull)
		{
			tcategory = JSONBTYPE_NULL;
			outfuncoid = InvalidOid;
		}
		else
			jsonb_categorize_type(att->atttypid, &tcategory, &outfuncoid);

		datum_to_jsonb(val, isnull, result, tcategory, outfuncoid, false);
	}

	result->res = pushJsonbValue(&result->parseState, WJB_END_OBJECT, NULL);
	ReleaseTupleDesc(tupdesc);
}