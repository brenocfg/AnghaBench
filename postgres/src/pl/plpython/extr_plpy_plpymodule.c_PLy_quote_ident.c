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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/ * PyString_FromString (char const*) ; 
 char* quote_identifier (char const*) ; 

__attribute__((used)) static PyObject *
PLy_quote_ident(PyObject *self, PyObject *args)
{
	const char *str;
	const char *quoted;
	PyObject   *ret;

	if (!PyArg_ParseTuple(args, "s:quote_ident", &str))
		return NULL;

	quoted = quote_identifier(str);
	ret = PyString_FromString(quoted);

	return ret;
}