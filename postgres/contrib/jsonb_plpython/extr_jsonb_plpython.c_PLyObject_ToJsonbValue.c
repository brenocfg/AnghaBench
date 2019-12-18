#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int boolean; } ;
struct TYPE_29__ {TYPE_1__ val; int /*<<< orphan*/  type; } ;
struct TYPE_28__ {scalar_t__ ob_type; } ;
typedef  TYPE_2__ PyObject ;
typedef  TYPE_3__ JsonbValue ;
typedef  int /*<<< orphan*/  JsonbParseState ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_3__* PLyMapping_ToJsonbValue (TYPE_2__*,int /*<<< orphan*/ **) ; 
 TYPE_3__* PLyNumber_ToJsonbValue (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  PLyObject_AsString (TYPE_2__*) ; 
 TYPE_3__* PLySequence_ToJsonbValue (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PLyString_ToJsonbValue (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ PyBool_Check (TYPE_2__*) ; 
 scalar_t__ PyMapping_Check (TYPE_2__*) ; 
 scalar_t__ PyNumber_Check (TYPE_2__*) ; 
 scalar_t__ PySequence_Check (TYPE_2__*) ; 
 scalar_t__ PyString_Check (TYPE_2__*) ; 
 scalar_t__ PyUnicode_Check (TYPE_2__*) ; 
 TYPE_2__* Py_None ; 
 TYPE_2__* Py_True ; 
 int /*<<< orphan*/  WJB_ELEM ; 
 int /*<<< orphan*/  WJB_VALUE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbvBool ; 
 int /*<<< orphan*/  jbvNull ; 
 TYPE_3__* palloc (int) ; 
 TYPE_3__* pushJsonbValue (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static JsonbValue *
PLyObject_ToJsonbValue(PyObject *obj, JsonbParseState **jsonb_state, bool is_elem)
{
	JsonbValue	buf;
	JsonbValue *out;

	if (!(PyString_Check(obj) || PyUnicode_Check(obj)))
	{
		if (PySequence_Check(obj))
			return PLySequence_ToJsonbValue(obj, jsonb_state);
		else if (PyMapping_Check(obj))
			return PLyMapping_ToJsonbValue(obj, jsonb_state);
	}

	/* Allocate JsonbValue in heap only if it is raw scalar value. */
	if (*jsonb_state)
		out = &buf;
	else
		out = palloc(sizeof(JsonbValue));

	if (obj == Py_None)
		out->type = jbvNull;
	else if (PyString_Check(obj) || PyUnicode_Check(obj))
		PLyString_ToJsonbValue(obj, out);

	/*
	 * PyNumber_Check() returns true for booleans, so boolean check should
	 * come first.
	 */
	else if (PyBool_Check(obj))
	{
		out->type = jbvBool;
		out->val.boolean = (obj == Py_True);
	}
	else if (PyNumber_Check(obj))
		out = PLyNumber_ToJsonbValue(obj, out);
	else
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 (errmsg("Python type \"%s\" cannot be transformed to jsonb",
						 PLyObject_AsString((PyObject *) obj->ob_type)))));

	/* Push result into 'jsonb_state' unless it is raw scalar value. */
	return (*jsonb_state ?
			pushJsonbValue(jsonb_state, is_elem ? WJB_ELEM : WJB_VALUE, out) :
			out);
}