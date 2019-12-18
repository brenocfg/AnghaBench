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
struct TYPE_3__ {size_t num; char** array; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int PyList_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PyRun_SimpleString (char*) ; 
 int /*<<< orphan*/ * PySys_GetObject (char*) ; 
 int /*<<< orphan*/ * PyUnicode_FromString (char const*) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 char* bstrdup (char const*) ; 
 int /*<<< orphan*/  da_push_back (TYPE_1__,char**) ; 
 scalar_t__ py_error () ; 
 TYPE_1__ python_paths ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static void add_to_python_path(const char *path)
{
	PyObject *py_path_str = NULL;
	PyObject *py_path = NULL;
	int ret;

	if (!path || !*path)
		return;

	for (size_t i = 0; i < python_paths.num; i++) {
		const char *python_path = python_paths.array[i];
		if (strcmp(path, python_path) == 0)
			return;
	}

	ret = PyRun_SimpleString("import sys");
	if (py_error() || ret != 0)
		goto fail;

	/* borrowed reference here */
	py_path = PySys_GetObject("path");
	if (py_error() || !py_path)
		goto fail;

	py_path_str = PyUnicode_FromString(path);
	ret = PyList_Append(py_path, py_path_str);
	if (py_error() || ret != 0)
		goto fail;

	char *new_path = bstrdup(path);
	da_push_back(python_paths, &new_path);

fail:
	Py_XDECREF(py_path_str);
}