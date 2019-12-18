#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char text ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int JsonTypeCategory ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DATEOID ; 
 int /*<<< orphan*/  DatumGetBool (int /*<<< orphan*/ ) ; 
 char* DatumGetTextPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IsValidJsonNumber (char*,int /*<<< orphan*/ ) ; 
#define  JSONTYPE_ARRAY 136 
#define  JSONTYPE_BOOL 135 
#define  JSONTYPE_CAST 134 
#define  JSONTYPE_COMPOSITE 133 
#define  JSONTYPE_DATE 132 
#define  JSONTYPE_JSON 131 
#define  JSONTYPE_NUMERIC 130 
#define  JSONTYPE_TIMESTAMP 129 
#define  JSONTYPE_TIMESTAMPTZ 128 
 int /*<<< orphan*/  JsonEncodeDateTime (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAXDATELEN ; 
 int /*<<< orphan*/  OidFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMESTAMPOID ; 
 int /*<<< orphan*/  TIMESTAMPTZOID ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  array_to_json_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  composite_to_json (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  escape_json (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* text_to_cstring (char*) ; 

__attribute__((used)) static void
datum_to_json(Datum val, bool is_null, StringInfo result,
			  JsonTypeCategory tcategory, Oid outfuncoid,
			  bool key_scalar)
{
	char	   *outputstr;
	text	   *jsontext;

	check_stack_depth();

	/* callers are expected to ensure that null keys are not passed in */
	Assert(!(key_scalar && is_null));

	if (is_null)
	{
		appendStringInfoString(result, "null");
		return;
	}

	if (key_scalar &&
		(tcategory == JSONTYPE_ARRAY ||
		 tcategory == JSONTYPE_COMPOSITE ||
		 tcategory == JSONTYPE_JSON ||
		 tcategory == JSONTYPE_CAST))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("key value must be scalar, not array, composite, or json")));

	switch (tcategory)
	{
		case JSONTYPE_ARRAY:
			array_to_json_internal(val, result, false);
			break;
		case JSONTYPE_COMPOSITE:
			composite_to_json(val, result, false);
			break;
		case JSONTYPE_BOOL:
			outputstr = DatumGetBool(val) ? "true" : "false";
			if (key_scalar)
				escape_json(result, outputstr);
			else
				appendStringInfoString(result, outputstr);
			break;
		case JSONTYPE_NUMERIC:
			outputstr = OidOutputFunctionCall(outfuncoid, val);

			/*
			 * Don't call escape_json for a non-key if it's a valid JSON
			 * number.
			 */
			if (!key_scalar && IsValidJsonNumber(outputstr, strlen(outputstr)))
				appendStringInfoString(result, outputstr);
			else
				escape_json(result, outputstr);
			pfree(outputstr);
			break;
		case JSONTYPE_DATE:
			{
				char		buf[MAXDATELEN + 1];

				JsonEncodeDateTime(buf, val, DATEOID, NULL);
				appendStringInfo(result, "\"%s\"", buf);
			}
			break;
		case JSONTYPE_TIMESTAMP:
			{
				char		buf[MAXDATELEN + 1];

				JsonEncodeDateTime(buf, val, TIMESTAMPOID, NULL);
				appendStringInfo(result, "\"%s\"", buf);
			}
			break;
		case JSONTYPE_TIMESTAMPTZ:
			{
				char		buf[MAXDATELEN + 1];

				JsonEncodeDateTime(buf, val, TIMESTAMPTZOID, NULL);
				appendStringInfo(result, "\"%s\"", buf);
			}
			break;
		case JSONTYPE_JSON:
			/* JSON and JSONB output will already be escaped */
			outputstr = OidOutputFunctionCall(outfuncoid, val);
			appendStringInfoString(result, outputstr);
			pfree(outputstr);
			break;
		case JSONTYPE_CAST:
			/* outfuncoid refers to a cast function, not an output function */
			jsontext = DatumGetTextPP(OidFunctionCall1(outfuncoid, val));
			outputstr = text_to_cstring(jsontext);
			appendStringInfoString(result, outputstr);
			pfree(outputstr);
			pfree(jsontext);
			break;
		default:
			outputstr = OidOutputFunctionCall(outfuncoid, val);
			escape_json(result, outputstr);
			pfree(outputstr);
			break;
	}
}