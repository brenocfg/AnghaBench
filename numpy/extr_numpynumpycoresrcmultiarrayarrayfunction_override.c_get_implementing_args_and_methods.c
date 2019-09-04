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
typedef  size_t Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int NPY_MAXARGS ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 scalar_t__ PyObject_IsInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t PySequence_Fast_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** PySequence_Fast_ITEMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 scalar_t__ Py_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_array_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pyobject_array_insert (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_implementing_args_and_methods(PyObject *relevant_args,
                                  PyObject **implementing_args,
                                  PyObject **methods)
{
    int num_implementing_args = 0;
    Py_ssize_t i;
    int j;

    PyObject **items = PySequence_Fast_ITEMS(relevant_args);
    Py_ssize_t length = PySequence_Fast_GET_SIZE(relevant_args);

    for (i = 0; i < length; i++) {
        int new_class = 1;
        PyObject *argument = items[i];

        /* Have we seen this type before? */
        for (j = 0; j < num_implementing_args; j++) {
            if (Py_TYPE(argument) == Py_TYPE(implementing_args[j])) {
                new_class = 0;
                break;
            }
        }
        if (new_class) {
            PyObject *method = get_array_function(argument);

            if (method != NULL) {
                int arg_index;

                if (num_implementing_args >= NPY_MAXARGS) {
                    PyErr_Format(
                        PyExc_TypeError,
                        "maximum number (%d) of distinct argument types " \
                        "implementing __array_function__ exceeded",
                        NPY_MAXARGS);
                    Py_DECREF(method);
                    goto fail;
                }

                /* "subclasses before superclasses, otherwise left to right" */
                arg_index = num_implementing_args;
                for (j = 0; j < num_implementing_args; j++) {
                    PyObject *other_type;
                    other_type = (PyObject *)Py_TYPE(implementing_args[j]);
                    if (PyObject_IsInstance(argument, other_type)) {
                        arg_index = j;
                        break;
                    }
                }
                Py_INCREF(argument);
                pyobject_array_insert(implementing_args, num_implementing_args,
                                      arg_index, argument);
                pyobject_array_insert(methods, num_implementing_args,
                                      arg_index, method);
                ++num_implementing_args;
            }
        }
    }
    return num_implementing_args;

fail:
    for (j = 0; j < num_implementing_args; j++) {
        Py_DECREF(implementing_args[j]);
        Py_DECREF(methods[j]);
    }
    return -1;
}