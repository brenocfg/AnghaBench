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
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_CallFunction (int /*<<< orphan*/ ,char*,char*,int,...) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ STRLEN (char*) ; 
 int /*<<< orphan*/ * call_load_module (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  py_find_module ; 
 scalar_t__ vim_strchr (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static PyObject *
find_module(char *fullname, char *tail, PyObject *new_path)
{
    PyObject	*find_module_result;
    PyObject	*module;
    char	*dot;

    if ((dot = (char *)vim_strchr((char_u *) tail, '.')))
    {
	/*
	 * There is a dot in the name: call find_module recursively without the
	 * first component
	 */
	PyObject	*newest_path;
	int		partlen = (int) (dot - 1 - tail);

	if (!(find_module_result = PyObject_CallFunction(py_find_module,
			"s#O", tail, partlen, new_path)))
	    return NULL;

	if (!(module = call_load_module(
			fullname,
			((int) (tail - fullname)) + partlen,
			find_module_result)))
	{
	    Py_DECREF(find_module_result);
	    return NULL;
	}

	Py_DECREF(find_module_result);

	if (!(newest_path = PyObject_GetAttrString(module, "__path__")))
	{
	    Py_DECREF(module);
	    return NULL;
	}

	Py_DECREF(module);

	module = find_module(fullname, dot + 1, newest_path);

	Py_DECREF(newest_path);

	return module;
    }
    else
    {
	if (!(find_module_result = PyObject_CallFunction(py_find_module,
			"sO", tail, new_path)))
	    return NULL;

	if (!(module = call_load_module(
			fullname,
			(int)STRLEN(fullname),
			find_module_result)))
	{
	    Py_DECREF(find_module_result);
	    return NULL;
	}

	Py_DECREF(find_module_result);

	return module;
    }
}