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
typedef  int /*<<< orphan*/  PyTypeObject ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * FunctionNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyErr_SET_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyMem_Free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
FunctionConstructor(PyTypeObject *subtype, PyObject *args, PyObject *kwargs)
{
    PyObject	*self;
    char_u	*name;

    if (kwargs)
    {
	PyErr_SET_STRING(PyExc_TypeError,
		N_("function constructor does not accept keyword arguments"));
	return NULL;
    }

    if (!PyArg_ParseTuple(args, "et", "ascii", &name))
	return NULL;

    self = FunctionNew(subtype, name);

    PyMem_Free(name);

    return self;
}