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
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*) ; 
 void stub1 () ; 

__attribute__((used)) static PyObject *mod_init(PyObject *capi_self, PyObject *capi_args,
                          PyObject *capi_keywds, void (*f2py_func)()) {
    PyObject *capi_buildvalue = NULL;
    static char *capi_kwlist[] = {NULL};
    if (!PyArg_ParseTupleAndKeywords(capi_args,capi_keywds,\
                                     "|:mod.init",\
                                     capi_kwlist))
        goto capi_fail;
    (*f2py_func)();
    capi_buildvalue = Py_BuildValue("");
 capi_fail:
    return capi_buildvalue;
}