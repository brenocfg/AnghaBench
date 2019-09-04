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
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
array_reduce_ex_regular(PyArrayObject *self, int protocol)
{
    PyObject *subclass_array_reduce = NULL;
    PyObject *ret;

    /* We do not call array_reduce directly but instead lookup and call
     * the __reduce__ method to make sure that it's possible to customize
     * pickling in sub-classes. */
    subclass_array_reduce = PyObject_GetAttrString((PyObject *)self,
                                                   "__reduce__");
    if (subclass_array_reduce == NULL) {
        return NULL;
    }
    ret = PyObject_CallObject(subclass_array_reduce, NULL);
    Py_DECREF(subclass_array_reduce);
    return ret;
}