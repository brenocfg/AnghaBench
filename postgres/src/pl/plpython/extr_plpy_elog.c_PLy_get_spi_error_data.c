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

/* Variables and functions */
 int /*<<< orphan*/  PLy_get_sqlerrcode (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int*,char**,char**,char**,int*,char**,char**,char**,char**,char**) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
PLy_get_spi_error_data(PyObject *exc, int *sqlerrcode, char **detail,
					   char **hint, char **query, int *position,
					   char **schema_name, char **table_name,
					   char **column_name,
					   char **datatype_name, char **constraint_name)
{
	PyObject   *spidata;

	spidata = PyObject_GetAttrString(exc, "spidata");

	if (spidata != NULL)
	{
		PyArg_ParseTuple(spidata, "izzzizzzzz",
						 sqlerrcode, detail, hint, query, position,
						 schema_name, table_name, column_name,
						 datatype_name, constraint_name);
	}
	else
	{
		/*
		 * If there's no spidata, at least set the sqlerrcode. This can happen
		 * if someone explicitly raises a SPI exception from Python code.
		 */
		PLy_get_sqlerrcode(exc, sqlerrcode);
	}

	Py_XDECREF(spidata);
}