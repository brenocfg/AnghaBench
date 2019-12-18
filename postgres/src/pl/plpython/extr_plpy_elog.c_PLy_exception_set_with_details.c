#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  constraint_name; int /*<<< orphan*/  datatype_name; int /*<<< orphan*/  column_name; int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; int /*<<< orphan*/  internalquery; int /*<<< orphan*/  hint; int /*<<< orphan*/  detail; int /*<<< orphan*/  sqlerrcode; int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_string_attr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpack_sql_state (int /*<<< orphan*/ ) ; 

void
PLy_exception_set_with_details(PyObject *excclass, ErrorData *edata)
{
	PyObject   *args = NULL;
	PyObject   *error = NULL;

	args = Py_BuildValue("(s)", edata->message);
	if (!args)
		goto failure;

	/* create a new exception with the error message as the parameter */
	error = PyObject_CallObject(excclass, args);
	if (!error)
		goto failure;

	if (!set_string_attr(error, "sqlstate",
						 unpack_sql_state(edata->sqlerrcode)))
		goto failure;

	if (!set_string_attr(error, "detail", edata->detail))
		goto failure;

	if (!set_string_attr(error, "hint", edata->hint))
		goto failure;

	if (!set_string_attr(error, "query", edata->internalquery))
		goto failure;

	if (!set_string_attr(error, "schema_name", edata->schema_name))
		goto failure;

	if (!set_string_attr(error, "table_name", edata->table_name))
		goto failure;

	if (!set_string_attr(error, "column_name", edata->column_name))
		goto failure;

	if (!set_string_attr(error, "datatype_name", edata->datatype_name))
		goto failure;

	if (!set_string_attr(error, "constraint_name", edata->constraint_name))
		goto failure;

	PyErr_SetObject(excclass, error);

	Py_DECREF(args);
	Py_DECREF(error);

	return;

failure:
	Py_XDECREF(args);
	Py_XDECREF(error);

	elog(ERROR, "could not convert error to Python exception");
}