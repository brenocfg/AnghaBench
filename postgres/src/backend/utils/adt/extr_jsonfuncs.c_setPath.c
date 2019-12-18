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
struct TYPE_10__ {int /*<<< orphan*/  nPairs; } ;
struct TYPE_9__ {int /*<<< orphan*/  nElems; } ;
struct TYPE_11__ {TYPE_2__ object; TYPE_1__ array; } ;
struct TYPE_12__ {TYPE_3__ val; } ;
typedef  TYPE_4__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  int JsonbIteratorToken ;
typedef  int /*<<< orphan*/  JsonbIterator ;
typedef  int /*<<< orphan*/  Jsonb ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_NULL_VALUE_NOT_ALLOWED ; 
 int /*<<< orphan*/  ERROR ; 
 int JsonbIteratorNext (int /*<<< orphan*/ **,TYPE_4__*,int) ; 
#define  WJB_BEGIN_ARRAY 131 
#define  WJB_BEGIN_OBJECT 130 
#define  WJB_ELEM 129 
 int WJB_END_ARRAY ; 
 int WJB_END_OBJECT ; 
#define  WJB_VALUE 128 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 TYPE_4__* pushJsonbValue (int /*<<< orphan*/ **,int,TYPE_4__*) ; 
 int /*<<< orphan*/  setPathArray (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setPathObject (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static JsonbValue *
setPath(JsonbIterator **it, Datum *path_elems,
		bool *path_nulls, int path_len,
		JsonbParseState **st, int level, Jsonb *newval, int op_type)
{
	JsonbValue	v;
	JsonbIteratorToken r;
	JsonbValue *res;

	check_stack_depth();

	if (path_nulls[level])
		ereport(ERROR,
				(errcode(ERRCODE_NULL_VALUE_NOT_ALLOWED),
				 errmsg("path element at position %d is null",
						level + 1)));

	r = JsonbIteratorNext(it, &v, false);

	switch (r)
	{
		case WJB_BEGIN_ARRAY:
			(void) pushJsonbValue(st, r, NULL);
			setPathArray(it, path_elems, path_nulls, path_len, st, level,
						 newval, v.val.array.nElems, op_type);
			r = JsonbIteratorNext(it, &v, false);
			Assert(r == WJB_END_ARRAY);
			res = pushJsonbValue(st, r, NULL);
			break;
		case WJB_BEGIN_OBJECT:
			(void) pushJsonbValue(st, r, NULL);
			setPathObject(it, path_elems, path_nulls, path_len, st, level,
						  newval, v.val.object.nPairs, op_type);
			r = JsonbIteratorNext(it, &v, true);
			Assert(r == WJB_END_OBJECT);
			res = pushJsonbValue(st, r, NULL);
			break;
		case WJB_ELEM:
		case WJB_VALUE:
			res = pushJsonbValue(st, r, &v);
			break;
		default:
			elog(ERROR, "unrecognized iterator result: %d", (int) r);
			res = NULL;			/* keep compiler quiet */
			break;
	}

	return res;
}