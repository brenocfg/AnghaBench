#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int int64 ;
struct TYPE_32__ {scalar_t__ id; scalar_t__ jbc; } ;
struct TYPE_31__ {TYPE_7__ baseObject; int /*<<< orphan*/  lastGeneratedObjectId; } ;
struct TYPE_30__ {int /*<<< orphan*/  type; } ;
struct TYPE_27__ {char* val; int len; } ;
struct TYPE_26__ {int /*<<< orphan*/ * data; } ;
struct TYPE_28__ {int /*<<< orphan*/  numeric; TYPE_2__ string; TYPE_1__ binary; } ;
struct TYPE_29__ {scalar_t__ type; TYPE_3__ val; } ;
typedef  TYPE_4__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  scalar_t__ JsonbIteratorToken ;
typedef  int /*<<< orphan*/  JsonbIterator ;
typedef  int /*<<< orphan*/  JsonbContainer ;
typedef  int /*<<< orphan*/  Jsonb ;
typedef  int /*<<< orphan*/  JsonValueList ;
typedef  TYPE_5__ JsonPathItem ;
typedef  int /*<<< orphan*/  JsonPathExecResult ;
typedef  TYPE_6__ JsonPathExecContext ;
typedef  TYPE_7__ JsonBaseObjectInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetNumeric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_SQL_JSON_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR ; 
 int INT64CONST (int) ; 
 int /*<<< orphan*/  Int64GetDatum (int) ; 
 int /*<<< orphan*/  JsonContainerSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonbInitBinary (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonbIteratorInit (int /*<<< orphan*/ *) ; 
 scalar_t__ JsonbIteratorNext (int /*<<< orphan*/ **,TYPE_4__*,int) ; 
 scalar_t__ JsonbType (TYPE_4__*) ; 
 int /*<<< orphan*/ * JsonbValueToJsonb (TYPE_4__*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ WJB_BEGIN_OBJECT ; 
 scalar_t__ WJB_DONE ; 
 scalar_t__ WJB_END_OBJECT ; 
 scalar_t__ WJB_KEY ; 
 scalar_t__ WJB_VALUE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  executeNextItem (TYPE_6__*,TYPE_5__*,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  int8_numeric ; 
 scalar_t__ jbvBinary ; 
 scalar_t__ jbvNumeric ; 
 scalar_t__ jbvObject ; 
 void* jbvString ; 
 scalar_t__ jperIsError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jperNotFound ; 
 int /*<<< orphan*/  jperOk ; 
 int jspGetNext (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  jspOperationName (int /*<<< orphan*/ ) ; 
 TYPE_4__* pushJsonbValue (int /*<<< orphan*/ **,scalar_t__,TYPE_4__*) ; 
 TYPE_7__ setBaseObject (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static JsonPathExecResult
executeKeyValueMethod(JsonPathExecContext *cxt, JsonPathItem *jsp,
					  JsonbValue *jb, JsonValueList *found)
{
	JsonPathExecResult res = jperNotFound;
	JsonPathItem next;
	JsonbContainer *jbc;
	JsonbValue	key;
	JsonbValue	val;
	JsonbValue	idval;
	JsonbValue	keystr;
	JsonbValue	valstr;
	JsonbValue	idstr;
	JsonbIterator *it;
	JsonbIteratorToken tok;
	int64		id;
	bool		hasNext;

	if (JsonbType(jb) != jbvObject || jb->type != jbvBinary)
		RETURN_ERROR(ereport(ERROR,
							 (errcode(ERRCODE_SQL_JSON_OBJECT_NOT_FOUND),
							  errmsg("jsonpath item method .%s() can only be applied to an object",
									 jspOperationName(jsp->type)))));

	jbc = jb->val.binary.data;

	if (!JsonContainerSize(jbc))
		return jperNotFound;	/* no key-value pairs */

	hasNext = jspGetNext(jsp, &next);

	keystr.type = jbvString;
	keystr.val.string.val = "key";
	keystr.val.string.len = 3;

	valstr.type = jbvString;
	valstr.val.string.val = "value";
	valstr.val.string.len = 5;

	idstr.type = jbvString;
	idstr.val.string.val = "id";
	idstr.val.string.len = 2;

	/* construct object id from its base object and offset inside that */
	id = jb->type != jbvBinary ? 0 :
		(int64) ((char *) jbc - (char *) cxt->baseObject.jbc);
	id += (int64) cxt->baseObject.id * INT64CONST(10000000000);

	idval.type = jbvNumeric;
	idval.val.numeric = DatumGetNumeric(DirectFunctionCall1(int8_numeric,
															Int64GetDatum(id)));

	it = JsonbIteratorInit(jbc);

	while ((tok = JsonbIteratorNext(&it, &key, true)) != WJB_DONE)
	{
		JsonBaseObjectInfo baseObject;
		JsonbValue	obj;
		JsonbParseState *ps;
		JsonbValue *keyval;
		Jsonb	   *jsonb;

		if (tok != WJB_KEY)
			continue;

		res = jperOk;

		if (!hasNext && !found)
			break;

		tok = JsonbIteratorNext(&it, &val, true);
		Assert(tok == WJB_VALUE);

		ps = NULL;
		pushJsonbValue(&ps, WJB_BEGIN_OBJECT, NULL);

		pushJsonbValue(&ps, WJB_KEY, &keystr);
		pushJsonbValue(&ps, WJB_VALUE, &key);

		pushJsonbValue(&ps, WJB_KEY, &valstr);
		pushJsonbValue(&ps, WJB_VALUE, &val);

		pushJsonbValue(&ps, WJB_KEY, &idstr);
		pushJsonbValue(&ps, WJB_VALUE, &idval);

		keyval = pushJsonbValue(&ps, WJB_END_OBJECT, NULL);

		jsonb = JsonbValueToJsonb(keyval);

		JsonbInitBinary(&obj, jsonb);

		baseObject = setBaseObject(cxt, &obj, cxt->lastGeneratedObjectId++);

		res = executeNextItem(cxt, jsp, &next, &obj, found, true);

		cxt->baseObject = baseObject;

		if (jperIsError(res))
			return res;

		if (res == jperOk && !found)
			break;
	}

	return res;
}