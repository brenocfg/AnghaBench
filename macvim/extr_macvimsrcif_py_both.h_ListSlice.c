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
typedef  int Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int PyInt ;
typedef  int /*<<< orphan*/  ListObject ;

/* Variables and functions */
 int /*<<< orphan*/ * ListIndex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyErr_SET_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyList_New (int) ; 
 int /*<<< orphan*/  PyList_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
ListSlice(ListObject *self, Py_ssize_t first, Py_ssize_t step,
	  Py_ssize_t slicelen)
{
    PyInt	i;
    PyObject	*list;

    if (step == 0)
    {
	PyErr_SET_STRING(PyExc_ValueError, N_("slice step cannot be zero"));
	return NULL;
    }

    list = PyList_New(slicelen);
    if (list == NULL)
	return NULL;

    for (i = 0; i < slicelen; ++i)
    {
	PyObject	*item;

	item = ListIndex(self, first + i*step);
	if (item == NULL)
	{
	    Py_DECREF(list);
	    return NULL;
	}

	PyList_SET_ITEM(list, i, item);
    }

    return list;
}