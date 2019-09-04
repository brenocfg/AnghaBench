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
typedef  int /*<<< orphan*/  WindowObject ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ CheckWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * Py_FindMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * WindowAttr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * WindowAttrValid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  WindowMethods ; 

__attribute__((used)) static PyObject *
WindowGetattr(PyObject *self, char *name)
{
    PyObject *r;

    if ((r = WindowAttrValid((WindowObject *)(self), name)))
	return r;

    if (CheckWindow((WindowObject *)(self)))
	return NULL;

    r = WindowAttr((WindowObject *)(self), name);
    if (r || PyErr_Occurred())
	return r;
    else
	return Py_FindMethod(WindowMethods, self, name);
}