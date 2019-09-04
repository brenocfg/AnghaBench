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
typedef  int /*<<< orphan*/  PyUnicodeObject ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ PyBool_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyFloat_CheckExact (int /*<<< orphan*/ *) ; 
 scalar_t__ PyInt_CheckExact (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_CheckExact (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PyObject_Unicode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/ * escape_unicode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  markup ; 

__attribute__((used)) static PyObject*
escape(PyObject *self, PyObject *text)
{
	PyObject *s = NULL, *rv = NULL, *html;

	/* we don't have to escape integers, bools or floats */
	if (PyLong_CheckExact(text) ||
#if PY_MAJOR_VERSION < 3
	    PyInt_CheckExact(text) ||
#endif
	    PyFloat_CheckExact(text) || PyBool_Check(text) ||
	    text == Py_None)
		return PyObject_CallFunctionObjArgs(markup, text, NULL);

	/* if the object has an __html__ method that performs the escaping */
	html = PyObject_GetAttrString(text, "__html__");
	if (html) {
		rv = PyObject_CallObject(html, NULL);
		Py_DECREF(html);
		return rv;
	}

	/* otherwise make the object unicode if it isn't, then escape */
	PyErr_Clear();
	if (!PyUnicode_Check(text)) {
#if PY_MAJOR_VERSION < 3
		PyObject *unicode = PyObject_Unicode(text);
#else
		PyObject *unicode = PyObject_Str(text);
#endif
		if (!unicode)
			return NULL;
		s = escape_unicode((PyUnicodeObject*)unicode);
		Py_DECREF(unicode);
	}
	else
		s = escape_unicode((PyUnicodeObject*)text);

	/* convert the unicode string into a markup object. */
	rv = PyObject_CallFunctionObjArgs(markup, (PyObject*)s, NULL);
	Py_DECREF(s);
	return rv;
}