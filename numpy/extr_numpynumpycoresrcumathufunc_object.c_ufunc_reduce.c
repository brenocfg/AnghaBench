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
typedef  int /*<<< orphan*/  PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int PyUFunc_CheckOverride (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * PyUFunc_GenericReduction (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UFUNC_REDUCE ; 

__attribute__((used)) static PyObject *
ufunc_reduce(PyUFuncObject *ufunc, PyObject *args, PyObject *kwds)
{
    int errval;
    PyObject *override = NULL;

    errval = PyUFunc_CheckOverride(ufunc, "reduce", args, kwds, &override);
    if (errval) {
        return NULL;
    }
    else if (override) {
        return override;
    }
    return PyUFunc_GenericReduction(ufunc, args, kwds, UFUNC_REDUCE);
}