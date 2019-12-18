#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_11__ {int /*<<< orphan*/  val; int /*<<< orphan*/  len; } ;
struct TYPE_12__ {TYPE_1__ string; void* numeric; } ;
struct TYPE_13__ {TYPE_2__ val; void* type; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;
typedef  int /*<<< orphan*/  IV ;
typedef  int /*<<< orphan*/  HV ;
typedef  int /*<<< orphan*/  AV ;

/* Variables and functions */
 TYPE_3__* AV_to_JsonbValue (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 void* DatumGetNumeric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  Float8GetDatum (double) ; 
 TYPE_3__* HV_to_JsonbValue (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
#define  SVt_PVAV 129 
#define  SVt_PVHV 128 
 int /*<<< orphan*/  SvIOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SvIV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SvNOK (int /*<<< orphan*/ *) ; 
 double SvNV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SvOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SvPOK (int /*<<< orphan*/ *) ; 
 char* SvPV_nolen (int /*<<< orphan*/ *) ; 
 scalar_t__ SvROK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SvRV (int /*<<< orphan*/ *) ; 
 int SvTYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SvUOK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WJB_ELEM ; 
 int /*<<< orphan*/  WJB_VALUE ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  float8_numeric ; 
 int /*<<< orphan*/  int8_numeric ; 
 int /*<<< orphan*/  isinf (double) ; 
 int /*<<< orphan*/  isnan (double) ; 
 void* jbvNull ; 
 void* jbvNumeric ; 
 void* jbvString ; 
 TYPE_3__* memcpy (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  numeric_in ; 
 int /*<<< orphan*/  palloc (int) ; 
 TYPE_3__* pushJsonbValue (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv2cstr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static JsonbValue *
SV_to_JsonbValue(SV *in, JsonbParseState **jsonb_state, bool is_elem)
{
	dTHX;
	JsonbValue	out;			/* result */

	/* Dereference references recursively. */
	while (SvROK(in))
		in = SvRV(in);

	switch (SvTYPE(in))
	{
		case SVt_PVAV:
			return AV_to_JsonbValue((AV *) in, jsonb_state);

		case SVt_PVHV:
			return HV_to_JsonbValue((HV *) in, jsonb_state);

		default:
			if (!SvOK(in))
			{
				out.type = jbvNull;
			}
			else if (SvUOK(in))
			{
				/*
				 * If UV is >=64 bits, we have no better way to make this
				 * happen than converting to text and back.  Given the low
				 * usage of UV in Perl code, it's not clear it's worth working
				 * hard to provide alternate code paths.
				 */
				const char *strval = SvPV_nolen(in);

				out.type = jbvNumeric;
				out.val.numeric =
					DatumGetNumeric(DirectFunctionCall3(numeric_in,
														CStringGetDatum(strval),
														ObjectIdGetDatum(InvalidOid),
														Int32GetDatum(-1)));
			}
			else if (SvIOK(in))
			{
				IV			ival = SvIV(in);

				out.type = jbvNumeric;
				out.val.numeric =
					DatumGetNumeric(DirectFunctionCall1(int8_numeric,
														Int64GetDatum((int64) ival)));
			}
			else if (SvNOK(in))
			{
				double		nval = SvNV(in);

				/*
				 * jsonb doesn't allow infinity or NaN (per JSON
				 * specification), but the numeric type that is used for the
				 * storage accepts NaN, so we have to prevent it here
				 * explicitly.  We don't really have to check for isinf()
				 * here, as numeric doesn't allow it and it would be caught
				 * later, but it makes for a nicer error message.
				 */
				if (isinf(nval))
					ereport(ERROR,
							(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
							 (errmsg("cannot convert infinity to jsonb"))));
				if (isnan(nval))
					ereport(ERROR,
							(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
							 (errmsg("cannot convert NaN to jsonb"))));

				out.type = jbvNumeric;
				out.val.numeric =
					DatumGetNumeric(DirectFunctionCall1(float8_numeric,
														Float8GetDatum(nval)));
			}
			else if (SvPOK(in))
			{
				out.type = jbvString;
				out.val.string.val = sv2cstr(in);
				out.val.string.len = strlen(out.val.string.val);
			}
			else
			{
				/*
				 * XXX It might be nice if we could include the Perl type in
				 * the error message.
				 */
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 (errmsg("cannot transform this Perl type to jsonb"))));
				return NULL;
			}
	}

	/* Push result into 'jsonb_state' unless it is a raw scalar. */
	return *jsonb_state
		? pushJsonbValue(jsonb_state, is_elem ? WJB_ELEM : WJB_VALUE, &out)
		: memcpy(palloc(sizeof(JsonbValue)), &out, sizeof(JsonbValue));
}