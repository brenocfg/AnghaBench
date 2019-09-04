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
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  scalar_t__ NPY_ORDER ;
typedef  int /*<<< orphan*/  NPY_CASTING ;

/* Variables and functions */
 scalar_t__ NPY_ANYORDER ; 
 scalar_t__ NPY_CORDER ; 
 scalar_t__ NPY_FORTRANORDER ; 
 scalar_t__ NPY_KEEPORDER ; 
 int /*<<< orphan*/  NPY_UNSAFE_CASTING ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * PyArray_AdaptFlexibleDType (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_CanCastArrayTo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_CastingConverter ; 
 scalar_t__ PyArray_CheckExact (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_CopyInto (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DescrConverter ; 
 scalar_t__ PyArray_EquivTypes (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PyArray_IS_C_CONTIGUOUS (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_IS_F_CONTIGUOUS (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NewLikeArray (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyArray_OrderConverter ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/ * PyObject_Repr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUString_ConcatAndDel (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUString_FromFormat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyUString_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npy_casting_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
array_astype(PyArrayObject *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"dtype", "order", "casting",
                             "subok", "copy", NULL};
    PyArray_Descr *dtype = NULL;
    /*
     * TODO: UNSAFE default for compatibility, I think
     *       switching to SAME_KIND by default would be good.
     */
    NPY_CASTING casting = NPY_UNSAFE_CASTING;
    NPY_ORDER order = NPY_KEEPORDER;
    int forcecopy = 1, subok = 1;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "O&|O&O&ii:astype", kwlist,
                            PyArray_DescrConverter, &dtype,
                            PyArray_OrderConverter, &order,
                            PyArray_CastingConverter, &casting,
                            &subok,
                            &forcecopy)) {
        Py_XDECREF(dtype);
        return NULL;
    }

    /*
     * If the memory layout matches and, data types are equivalent,
     * and it's not a subtype if subok is False, then we
     * can skip the copy.
     */
    if (!forcecopy && (order == NPY_KEEPORDER ||
                       (order == NPY_ANYORDER &&
                            (PyArray_IS_C_CONTIGUOUS(self) ||
                            PyArray_IS_F_CONTIGUOUS(self))) ||
                       (order == NPY_CORDER &&
                            PyArray_IS_C_CONTIGUOUS(self)) ||
                       (order == NPY_FORTRANORDER &&
                            PyArray_IS_F_CONTIGUOUS(self))) &&
                    (subok || PyArray_CheckExact(self)) &&
                    PyArray_EquivTypes(dtype, PyArray_DESCR(self))) {
        Py_DECREF(dtype);
        Py_INCREF(self);
        return (PyObject *)self;
    }
    else if (PyArray_CanCastArrayTo(self, dtype, casting)) {
        PyArrayObject *ret;

        /* If the requested dtype is flexible, adapt it */
        dtype = PyArray_AdaptFlexibleDType((PyObject *)self,
                                           PyArray_DESCR(self), dtype);
        if (dtype == NULL) {
            return NULL;
        }

        /* This steals the reference to dtype, so no DECREF of dtype */
        ret = (PyArrayObject *)PyArray_NewLikeArray(
                                    self, order, dtype, subok);
        if (ret == NULL) {
            return NULL;
        }

        if (PyArray_CopyInto(ret, self) < 0) {
            Py_DECREF(ret);
            return NULL;
        }

        return (PyObject *)ret;
    }
    else {
        PyObject *errmsg;
        errmsg = PyUString_FromString("Cannot cast array from ");
        PyUString_ConcatAndDel(&errmsg,
                PyObject_Repr((PyObject *)PyArray_DESCR(self)));
        PyUString_ConcatAndDel(&errmsg,
                PyUString_FromString(" to "));
        PyUString_ConcatAndDel(&errmsg,
                PyObject_Repr((PyObject *)dtype));
        PyUString_ConcatAndDel(&errmsg,
                PyUString_FromFormat(" according to the rule %s",
                        npy_casting_to_string(casting)));
        PyErr_SetObject(PyExc_TypeError, errmsg);
        Py_DECREF(errmsg);
        Py_DECREF(dtype);
        return NULL;
    }
}