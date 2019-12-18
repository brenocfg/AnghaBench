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
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PLyDatumToOb ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 char* DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PLy_elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/ * PyImport_ImportModule (char*) ; 
 int /*<<< orphan*/ * PyObject_CallFunction (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  numeric_out ; 

__attribute__((used)) static PyObject *
PLyDecimal_FromNumeric(PLyDatumToOb *arg, Datum d)
{
	static PyObject *decimal_constructor;
	char	   *str;
	PyObject   *pyvalue;

	/* Try to import cdecimal.  If it doesn't exist, fall back to decimal. */
	if (!decimal_constructor)
	{
		PyObject   *decimal_module;

		decimal_module = PyImport_ImportModule("cdecimal");
		if (!decimal_module)
		{
			PyErr_Clear();
			decimal_module = PyImport_ImportModule("decimal");
		}
		if (!decimal_module)
			PLy_elog(ERROR, "could not import a module for Decimal constructor");

		decimal_constructor = PyObject_GetAttrString(decimal_module, "Decimal");
		if (!decimal_constructor)
			PLy_elog(ERROR, "no Decimal attribute in module");
	}

	str = DatumGetCString(DirectFunctionCall1(numeric_out, d));
	pyvalue = PyObject_CallFunction(decimal_constructor, "s", str);
	if (!pyvalue)
		PLy_elog(ERROR, "conversion from numeric to Decimal failed");

	return pyvalue;
}