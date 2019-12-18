#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  numeric; } ;
struct TYPE_6__ {TYPE_1__ val; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  Numeric ;
typedef  TYPE_2__ JsonbValue ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CStringGetDatum (char*) ; 
 int /*<<< orphan*/  DatumGetNumeric (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  Int32GetDatum (int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 char* PLyObject_AsString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  jbvNumeric ; 
 int /*<<< orphan*/  numeric_in ; 
 scalar_t__ numeric_is_nan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static JsonbValue *
PLyNumber_ToJsonbValue(PyObject *obj, JsonbValue *jbvNum)
{
	Numeric		num;
	char	   *str = PLyObject_AsString(obj);

	PG_TRY();
	{
		Datum		numd;

		numd = DirectFunctionCall3(numeric_in,
								   CStringGetDatum(str),
								   ObjectIdGetDatum(InvalidOid),
								   Int32GetDatum(-1));
		num = DatumGetNumeric(numd);
	}
	PG_CATCH();
	{
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 (errmsg("could not convert value \"%s\" to jsonb", str))));
	}
	PG_END_TRY();

	pfree(str);

	/*
	 * jsonb doesn't allow NaN (per JSON specification), so we have to prevent
	 * it here explicitly.  (Infinity is also not allowed in jsonb, but
	 * numeric_in above already catches that.)
	 */
	if (numeric_is_nan(num))
		ereport(ERROR,
				(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
				 (errmsg("cannot convert NaN to jsonb"))));

	jbvNum->type = jbvNumeric;
	jbvNum->val.numeric = num;

	return jbvNum;
}