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
 int PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

int
F2PyDict_SetItemString(PyObject *dict, char *name, PyObject *obj)
{
    if (obj==NULL) {
        fprintf(stderr, "Error loading %s\n", name);
        if (PyErr_Occurred()) {
            PyErr_Print();
            PyErr_Clear();
        }
        return -1;
    }
    return PyDict_SetItemString(dict, name, obj);
}