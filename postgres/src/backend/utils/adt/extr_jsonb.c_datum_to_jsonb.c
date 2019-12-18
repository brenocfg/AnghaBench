#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  sem ;
struct TYPE_18__ {int rawScalar; int nElems; } ;
struct TYPE_19__ {char* val; void* len; } ;
struct TYPE_20__ {TYPE_1__ array; TYPE_2__ string; int /*<<< orphan*/  numeric; int /*<<< orphan*/  boolean; } ;
struct TYPE_21__ {int type; TYPE_3__ val; } ;
struct TYPE_25__ {TYPE_4__ contVal; } ;
struct TYPE_24__ {int /*<<< orphan*/  object_field_start; int /*<<< orphan*/  scalar; int /*<<< orphan*/  array_end; int /*<<< orphan*/  object_end; int /*<<< orphan*/  array_start; int /*<<< orphan*/  object_start; void* semstate; } ;
struct TYPE_23__ {int /*<<< orphan*/  root; } ;
struct TYPE_22__ {TYPE_8__* parseState; void* res; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ JsonbValue ;
typedef  int JsonbTypeCategory ;
typedef  int /*<<< orphan*/  JsonbIteratorToken ;
typedef  int /*<<< orphan*/  JsonbIterator ;
typedef  TYPE_5__ JsonbInState ;
typedef  TYPE_6__ Jsonb ;
typedef  TYPE_7__ JsonSemAction ;
typedef  int /*<<< orphan*/  JsonLexContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  DATEOID ; 
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 TYPE_6__* DatumGetJsonbP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetNumeric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetTextPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  JB_ROOT_IS_SCALAR (TYPE_6__*) ; 
#define  JSONBTYPE_ARRAY 139 
#define  JSONBTYPE_BOOL 138 
#define  JSONBTYPE_COMPOSITE 137 
#define  JSONBTYPE_DATE 136 
#define  JSONBTYPE_JSON 135 
#define  JSONBTYPE_JSONB 134 
#define  JSONBTYPE_JSONCAST 133 
#define  JSONBTYPE_NUMERIC 132 
#define  JSONBTYPE_TIMESTAMP 131 
#define  JSONBTYPE_TIMESTAMPTZ 130 
 void* JsonEncodeDateTime (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonbIteratorInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonbIteratorNext (int /*<<< orphan*/ **,TYPE_4__*,int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMESTAMPOID ; 
 int /*<<< orphan*/  TIMESTAMPTZOID ; 
 int /*<<< orphan*/  WJB_BEGIN_ARRAY ; 
 int /*<<< orphan*/  WJB_BEGIN_OBJECT ; 
 int /*<<< orphan*/  WJB_DONE ; 
 int /*<<< orphan*/  WJB_ELEM ; 
 int /*<<< orphan*/  WJB_END_ARRAY ; 
 int /*<<< orphan*/  WJB_END_OBJECT ; 
 int /*<<< orphan*/  WJB_KEY ; 
 int /*<<< orphan*/  WJB_VALUE ; 
 int /*<<< orphan*/  array_to_jsonb_internal (int /*<<< orphan*/ ,TYPE_5__*) ; 
 void* checkStringLen (void*) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  composite_to_jsonb (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
#define  jbvArray 129 
 int jbvBool ; 
 int jbvNull ; 
 int jbvNumeric ; 
#define  jbvObject 128 
 void* jbvString ; 
 int /*<<< orphan*/  jsonb_in_array_end ; 
 int /*<<< orphan*/  jsonb_in_array_start ; 
 int /*<<< orphan*/  jsonb_in_object_end ; 
 int /*<<< orphan*/  jsonb_in_object_field_start ; 
 int /*<<< orphan*/  jsonb_in_object_start ; 
 int /*<<< orphan*/  jsonb_in_scalar ; 
 int /*<<< orphan*/ * makeJsonLexContext (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numeric_in ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pg_parse_json (int /*<<< orphan*/ *,TYPE_7__*) ; 
 void* pushJsonbValue (TYPE_8__**,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 void* strlen (char*) ; 

__attribute__((used)) static void
datum_to_jsonb(Datum val, bool is_null, JsonbInState *result,
			   JsonbTypeCategory tcategory, Oid outfuncoid,
			   bool key_scalar)
{
	char	   *outputstr;
	bool		numeric_error;
	JsonbValue	jb;
	bool		scalar_jsonb = false;

	check_stack_depth();

	/* Convert val to a JsonbValue in jb (in most cases) */
	if (is_null)
	{
		Assert(!key_scalar);
		jb.type = jbvNull;
	}
	else if (key_scalar &&
			 (tcategory == JSONBTYPE_ARRAY ||
			  tcategory == JSONBTYPE_COMPOSITE ||
			  tcategory == JSONBTYPE_JSON ||
			  tcategory == JSONBTYPE_JSONB ||
			  tcategory == JSONBTYPE_JSONCAST))
	{
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("key value must be scalar, not array, composite, or json")));
	}
	else
	{
		if (tcategory == JSONBTYPE_JSONCAST)
			val = OidFunctionCall1(outfuncoid, val);

		switch (tcategory)
		{
			case JSONBTYPE_ARRAY:
				array_to_jsonb_internal(val, result);
				break;
			case JSONBTYPE_COMPOSITE:
				composite_to_jsonb(val, result);
				break;
			case JSONBTYPE_BOOL:
				if (key_scalar)
				{
					outputstr = DatumGetBool(val) ? "true" : "false";
					jb.type = jbvString;
					jb.val.string.len = strlen(outputstr);
					jb.val.string.val = outputstr;
				}
				else
				{
					jb.type = jbvBool;
					jb.val.boolean = DatumGetBool(val);
				}
				break;
			case JSONBTYPE_NUMERIC:
				outputstr = OidOutputFunctionCall(outfuncoid, val);
				if (key_scalar)
				{
					/* always quote keys */
					jb.type = jbvString;
					jb.val.string.len = strlen(outputstr);
					jb.val.string.val = outputstr;
				}
				else
				{
					/*
					 * Make it numeric if it's a valid JSON number, otherwise
					 * a string. Invalid numeric output will always have an
					 * 'N' or 'n' in it (I think).
					 */
					numeric_error = (strchr(outputstr, 'N') != NULL ||
									 strchr(outputstr, 'n') != NULL);
					if (!numeric_error)
					{
						Datum		numd;

						jb.type = jbvNumeric;
						numd = DirectFunctionCall3(numeric_in,
												   CStringGetDatum(outputstr),
												   ObjectIdGetDatum(InvalidOid),
												   Int32GetDatum(-1));
						jb.val.numeric = DatumGetNumeric(numd);
						pfree(outputstr);
					}
					else
					{
						jb.type = jbvString;
						jb.val.string.len = strlen(outputstr);
						jb.val.string.val = outputstr;
					}
				}
				break;
			case JSONBTYPE_DATE:
				jb.type = jbvString;
				jb.val.string.val = JsonEncodeDateTime(NULL, val,
													   DATEOID, NULL);
				jb.val.string.len = strlen(jb.val.string.val);
				break;
			case JSONBTYPE_TIMESTAMP:
				jb.type = jbvString;
				jb.val.string.val = JsonEncodeDateTime(NULL, val,
													   TIMESTAMPOID, NULL);
				jb.val.string.len = strlen(jb.val.string.val);
				break;
			case JSONBTYPE_TIMESTAMPTZ:
				jb.type = jbvString;
				jb.val.string.val = JsonEncodeDateTime(NULL, val,
													   TIMESTAMPTZOID, NULL);
				jb.val.string.len = strlen(jb.val.string.val);
				break;
			case JSONBTYPE_JSONCAST:
			case JSONBTYPE_JSON:
				{
					/* parse the json right into the existing result object */
					JsonLexContext *lex;
					JsonSemAction sem;
					text	   *json = DatumGetTextPP(val);

					lex = makeJsonLexContext(json, true);

					memset(&sem, 0, sizeof(sem));

					sem.semstate = (void *) result;

					sem.object_start = jsonb_in_object_start;
					sem.array_start = jsonb_in_array_start;
					sem.object_end = jsonb_in_object_end;
					sem.array_end = jsonb_in_array_end;
					sem.scalar = jsonb_in_scalar;
					sem.object_field_start = jsonb_in_object_field_start;

					pg_parse_json(lex, &sem);

				}
				break;
			case JSONBTYPE_JSONB:
				{
					Jsonb	   *jsonb = DatumGetJsonbP(val);
					JsonbIterator *it;

					it = JsonbIteratorInit(&jsonb->root);

					if (JB_ROOT_IS_SCALAR(jsonb))
					{
						(void) JsonbIteratorNext(&it, &jb, true);
						Assert(jb.type == jbvArray);
						(void) JsonbIteratorNext(&it, &jb, true);
						scalar_jsonb = true;
					}
					else
					{
						JsonbIteratorToken type;

						while ((type = JsonbIteratorNext(&it, &jb, false))
							   != WJB_DONE)
						{
							if (type == WJB_END_ARRAY || type == WJB_END_OBJECT ||
								type == WJB_BEGIN_ARRAY || type == WJB_BEGIN_OBJECT)
								result->res = pushJsonbValue(&result->parseState,
															 type, NULL);
							else
								result->res = pushJsonbValue(&result->parseState,
															 type, &jb);
						}
					}
				}
				break;
			default:
				outputstr = OidOutputFunctionCall(outfuncoid, val);
				jb.type = jbvString;
				jb.val.string.len = checkStringLen(strlen(outputstr));
				jb.val.string.val = outputstr;
				break;
		}
	}

	/* Now insert jb into result, unless we did it recursively */
	if (!is_null && !scalar_jsonb &&
		tcategory >= JSONBTYPE_JSON && tcategory <= JSONBTYPE_JSONCAST)
	{
		/* work has been done recursively */
		return;
	}
	else if (result->parseState == NULL)
	{
		/* single root scalar */
		JsonbValue	va;

		va.type = jbvArray;
		va.val.array.rawScalar = true;
		va.val.array.nElems = 1;

		result->res = pushJsonbValue(&result->parseState, WJB_BEGIN_ARRAY, &va);
		result->res = pushJsonbValue(&result->parseState, WJB_ELEM, &jb);
		result->res = pushJsonbValue(&result->parseState, WJB_END_ARRAY, NULL);
	}
	else
	{
		JsonbValue *o = &result->parseState->contVal;

		switch (o->type)
		{
			case jbvArray:
				result->res = pushJsonbValue(&result->parseState, WJB_ELEM, &jb);
				break;
			case jbvObject:
				result->res = pushJsonbValue(&result->parseState,
											 key_scalar ? WJB_KEY : WJB_VALUE,
											 &jb);
				break;
			default:
				elog(ERROR, "unexpected parent of nested structure");
		}
	}
}