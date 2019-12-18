#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_1__* ob_type; } ;
struct TYPE_19__ {int /*<<< orphan*/  tp_name; } ;
typedef  TYPE_2__ PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 TYPE_2__** PySequence_Fast_ITEMS (TYPE_2__*) ; 
 int PyTuple_Size (TYPE_2__*) ; 
 TYPE_2__* PyUFuncOverride_GetNonDefaultArrayUfunc (TYPE_2__*) ; 
 int PyUFuncOverride_GetOutObjects (TYPE_2__*,TYPE_2__**,TYPE_2__***) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_2__*) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_2__*) ; 
 TYPE_2__* Py_None ; 
 scalar_t__ Py_TYPE (TYPE_2__*) ; 

__attribute__((used)) static int
get_array_ufunc_overrides(PyObject *args, PyObject *kwds,
                          PyObject **with_override, PyObject **methods)
{
    int i;
    int num_override_args = 0;
    int narg, nout = 0;
    PyObject *out_kwd_obj;
    PyObject **arg_objs, **out_objs;

    narg = PyTuple_Size(args);
    if (narg < 0) {
        return -1;
    }
    arg_objs = PySequence_Fast_ITEMS(args);

    nout = PyUFuncOverride_GetOutObjects(kwds, &out_kwd_obj, &out_objs);
    if (nout < 0) {
        return -1;
    }

    for (i = 0; i < narg + nout; ++i) {
        PyObject *obj;
        int j;
        int new_class = 1;

        if (i < narg) {
            obj = arg_objs[i];
        }
        else {
            obj = out_objs[i - narg];
        }
        /*
         * Have we seen this class before?  If so, ignore.
         */
        for (j = 0; j < num_override_args; j++) {
            new_class = (Py_TYPE(obj) != Py_TYPE(with_override[j]));
            if (!new_class) {
                break;
            }
        }
        if (new_class) {
            /*
             * Now see if the object provides an __array_ufunc__. However, we should
             * ignore the base ndarray.__ufunc__, so we skip any ndarray as well as
             * any ndarray subclass instances that did not override __array_ufunc__.
             */
            PyObject *method = PyUFuncOverride_GetNonDefaultArrayUfunc(obj);
            if (method == NULL) {
                continue;
            }
            if (method == Py_None) {
                PyErr_Format(PyExc_TypeError,
                             "operand '%.200s' does not support ufuncs "
                             "(__array_ufunc__=None)",
                             obj->ob_type->tp_name);
                Py_DECREF(method);
                goto fail;
            }
            Py_INCREF(obj);
            with_override[num_override_args] = obj;
            methods[num_override_args] = method;
            ++num_override_args;
        }
    }
    Py_DECREF(out_kwd_obj);
    return num_override_args;

fail:
    for (i = 0; i < num_override_args; i++) {
        Py_DECREF(with_override[i]);
        Py_DECREF(methods[i]);
    }
    Py_DECREF(out_kwd_obj);
    return -1;
}