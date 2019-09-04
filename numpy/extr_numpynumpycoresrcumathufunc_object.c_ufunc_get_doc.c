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
struct TYPE_3__ {int /*<<< orphan*/ * doc; } ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_CallFunctionObjArgs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUString_ConcatAndDel (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyUString_FromFormat (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npy_cache_import (char*,char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static PyObject *
ufunc_get_doc(PyUFuncObject *ufunc)
{
    static PyObject *_sig_formatter;
    PyObject *doc;

    npy_cache_import(
        "numpy.core._internal",
        "_ufunc_doc_signature_formatter",
        &_sig_formatter);

    if (_sig_formatter == NULL) {
        return NULL;
    }

    /*
     * Put docstring first or FindMethod finds it... could so some
     * introspection on name and nin + nout to automate the first part
     * of it the doc string shouldn't need the calling convention
     */
    doc = PyObject_CallFunctionObjArgs(
        _sig_formatter, (PyObject *)ufunc, NULL);
    if (doc == NULL) {
        return NULL;
    }
    if (ufunc->doc != NULL) {
        PyUString_ConcatAndDel(&doc,
            PyUString_FromFormat("\n\n%s", ufunc->doc));
    }
    return doc;
}