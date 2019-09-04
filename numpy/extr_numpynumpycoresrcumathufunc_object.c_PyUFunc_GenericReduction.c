#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_68__   TYPE_2__ ;
typedef  struct TYPE_67__   TYPE_1__ ;

/* Type definitions */
struct TYPE_68__ {int /*<<< orphan*/  type_num; scalar_t__ elsize; } ;
struct TYPE_67__ {int nin; int nout; int /*<<< orphan*/  name; scalar_t__ core_enabled; } ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  TYPE_2__ PyObject ;
typedef  TYPE_2__ PyArray_Descr ;
typedef  TYPE_2__ PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  Generic ; 
 int /*<<< orphan*/  NPY_ARRAY_CARRAY ; 
 int NPY_INTP ; 
 int NPY_LONG ; 
 int NPY_MAXDIMS ; 
 int NPY_ULONG ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (TYPE_2__*,TYPE_2__*,char*,char**,TYPE_2__**,TYPE_2__**,TYPE_2__**,TYPE_2__**,TYPE_2__**,TYPE_2__**,...) ; 
 int /*<<< orphan*/  PyArray_Check (TYPE_2__*) ; 
 TYPE_2__* PyArray_DESCR (TYPE_2__*) ; 
 int /*<<< orphan*/  PyArray_DescrConverter2 ; 
 TYPE_2__* PyArray_DescrFromType (int) ; 
 scalar_t__ PyArray_FromAny (TYPE_2__*,TYPE_2__*,int,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ PyArray_ISFLEXIBLE (TYPE_2__*) ; 
 int /*<<< orphan*/  PyArray_IsScalar (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int PyArray_NDIM (TYPE_2__*) ; 
 int /*<<< orphan*/  PyArray_OutputConverter ; 
 int PyArray_PyIntAsInt (TYPE_2__*) ; 
 int PyArray_TYPE (TYPE_2__*) ; 
 int /*<<< orphan*/  PyCallable_Check (TYPE_2__*) ; 
 TYPE_2__* PyDict_GetItem (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyDict_SetItem (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 TYPE_2__* PyObject_GetAttr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PyTuple_Check (TYPE_2__*) ; 
 scalar_t__ PyTuple_CheckExact (TYPE_2__*) ; 
 TYPE_2__* PyTuple_GET_ITEM (TYPE_2__*,int) ; 
 int PyTuple_GET_SIZE (TYPE_2__*) ; 
 int PyTuple_Size (TYPE_2__*) ; 
 scalar_t__ PyTypeNum_ISBOOL (int) ; 
 scalar_t__ PyTypeNum_ISFLEXIBLE (int /*<<< orphan*/ ) ; 
 scalar_t__ PyTypeNum_ISINTEGER (int) ; 
 scalar_t__ PyTypeNum_ISUNSIGNED (int) ; 
 scalar_t__ PyUFunc_Accumulate (TYPE_1__*,TYPE_2__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* PyUFunc_Reduce (TYPE_1__*,TYPE_2__*,TYPE_2__*,int,int*,TYPE_2__*,int,TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ PyUFunc_Reduceat (TYPE_1__*,TYPE_2__*,TYPE_2__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* Py_BuildValue (char*,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_2__*) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_2__*) ; 
 TYPE_2__* Py_None ; 
 scalar_t__ Py_TYPE (TYPE_2__*) ; 
 int /*<<< orphan*/  Py_XDECREF (TYPE_2__*) ; 
#define  UFUNC_ACCUMULATE 130 
#define  UFUNC_REDUCE 129 
#define  UFUNC_REDUCEAT 128 
 TYPE_2__* _apply_array_wrap (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _wheremask_converter ; 
 scalar_t__ check_and_adjust_axis (int*,int) ; 
 scalar_t__ error_converting (int) ; 
 int /*<<< orphan*/  npy_um_str_array_wrap ; 
 int /*<<< orphan*/  npy_um_str_out ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static PyObject *
PyUFunc_GenericReduction(PyUFuncObject *ufunc, PyObject *args,
                         PyObject *kwds, int operation)
{
    int i, naxes=0, ndim;
    int axes[NPY_MAXDIMS];
    PyObject *axes_in = NULL;
    PyArrayObject *mp = NULL, *wheremask = NULL, *ret = NULL;
    PyObject *op;
    PyObject *obj_ind, *context;
    PyArrayObject *indices = NULL;
    PyArray_Descr *otype = NULL;
    PyArrayObject *out = NULL;
    int keepdims = 0;
    PyObject *initial = NULL;
    static char *reduce_kwlist[] = {
        "array", "axis", "dtype", "out", "keepdims", "initial", "where", NULL};
    static char *accumulate_kwlist[] = {
            "array", "axis", "dtype", "out", NULL};
    static char *reduceat_kwlist[] = {
            "array", "indices", "axis", "dtype", "out", NULL};

    static char *_reduce_type[] = {"reduce", "accumulate", "reduceat", NULL};

    if (ufunc == NULL) {
        PyErr_SetString(PyExc_ValueError, "function not supported");
        return NULL;
    }
    if (ufunc->core_enabled) {
        PyErr_Format(PyExc_RuntimeError,
                     "Reduction not defined on ufunc with signature");
        return NULL;
    }
    if (ufunc->nin != 2) {
        PyErr_Format(PyExc_ValueError,
                     "%s only supported for binary functions",
                     _reduce_type[operation]);
        return NULL;
    }
    if (ufunc->nout != 1) {
        PyErr_Format(PyExc_ValueError,
                     "%s only supported for functions "
                     "returning a single value",
                     _reduce_type[operation]);
        return NULL;
    }
    /* if there is a tuple of 1 for `out` in kwds, unpack it */
    if (kwds != NULL) {
        PyObject *out_obj = PyDict_GetItem(kwds, npy_um_str_out);
        if (out_obj != NULL && PyTuple_CheckExact(out_obj)) {
            if (PyTuple_GET_SIZE(out_obj) != 1) {
                PyErr_SetString(PyExc_ValueError,
                                "The 'out' tuple must have exactly one entry");
                return NULL;
            }
            out_obj = PyTuple_GET_ITEM(out_obj, 0);
            PyDict_SetItem(kwds, npy_um_str_out, out_obj);
        }
    }

    if (operation == UFUNC_REDUCEAT) {
        PyArray_Descr *indtype;
        indtype = PyArray_DescrFromType(NPY_INTP);
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "OO|OO&O&:reduceat", reduceat_kwlist,
                                         &op,
                                         &obj_ind,
                                         &axes_in,
                                         PyArray_DescrConverter2, &otype,
                                         PyArray_OutputConverter, &out)) {
            goto fail;
        }
        indices = (PyArrayObject *)PyArray_FromAny(obj_ind, indtype,
                                           1, 1, NPY_ARRAY_CARRAY, NULL);
        if (indices == NULL) {
            goto fail;
        }
    }
    else if (operation == UFUNC_ACCUMULATE) {
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|OO&O&:accumulate",
                                         accumulate_kwlist,
                                         &op,
                                         &axes_in,
                                         PyArray_DescrConverter2, &otype,
                                         PyArray_OutputConverter, &out)) {
            goto fail;
        }
    }
    else {
        if (!PyArg_ParseTupleAndKeywords(args, kwds, "O|OO&O&iOO&:reduce",
                                         reduce_kwlist,
                                         &op,
                                         &axes_in,
                                         PyArray_DescrConverter2, &otype,
                                         PyArray_OutputConverter, &out,
                                         &keepdims, &initial,
                                         _wheremask_converter, &wheremask)) {
            goto fail;
        }
    }
    /* Ensure input is an array */
    if (!PyArray_Check(op) && !PyArray_IsScalar(op, Generic)) {
        context = Py_BuildValue("O(O)i", ufunc, op, 0);
    }
    else {
        context = NULL;
    }
    mp = (PyArrayObject *)PyArray_FromAny(op, NULL, 0, 0, 0, context);
    Py_XDECREF(context);
    if (mp == NULL) {
        goto fail;
    }

    ndim = PyArray_NDIM(mp);

    /* Check to see that type (and otype) is not FLEXIBLE */
    if (PyArray_ISFLEXIBLE(mp) ||
        (otype && PyTypeNum_ISFLEXIBLE(otype->type_num))) {
        PyErr_Format(PyExc_TypeError,
                     "cannot perform %s with flexible type",
                     _reduce_type[operation]);
        goto fail;
    }

    /* Convert the 'axis' parameter into a list of axes */
    if (axes_in == NULL) {
        /* apply defaults */
        if (ndim == 0) {
            naxes = 0;
        }
        else {
            naxes = 1;
            axes[0] = 0;
        }
    }
    else if (axes_in == Py_None) {
        /* Convert 'None' into all the axes */
        naxes = ndim;
        for (i = 0; i < naxes; ++i) {
            axes[i] = i;
        }
    }
    else if (PyTuple_Check(axes_in)) {
        naxes = PyTuple_Size(axes_in);
        if (naxes < 0 || naxes > NPY_MAXDIMS) {
            PyErr_SetString(PyExc_ValueError,
                    "too many values for 'axis'");
            goto fail;
        }
        for (i = 0; i < naxes; ++i) {
            PyObject *tmp = PyTuple_GET_ITEM(axes_in, i);
            int axis = PyArray_PyIntAsInt(tmp);
            if (error_converting(axis)) {
                goto fail;
            }
            if (check_and_adjust_axis(&axis, ndim) < 0) {
                goto fail;
            }
            axes[i] = (int)axis;
        }
    }
    else {
        /* Try to interpret axis as an integer */
        int axis = PyArray_PyIntAsInt(axes_in);
        /* TODO: PyNumber_Index would be good to use here */
        if (error_converting(axis)) {
            goto fail;
        }
        /*
         * As a special case for backwards compatibility in 'sum',
         * 'prod', et al, also allow a reduction for scalars even
         * though this is technically incorrect.
         */
        if (ndim == 0 && (axis == 0 || axis == -1)) {
            naxes = 0;
        }
        else if (check_and_adjust_axis(&axis, ndim) < 0) {
            goto fail;
        }
        else {
            axes[0] = (int)axis;
            naxes = 1;
        }
    }

     /*
      * If out is specified it determines otype
      * unless otype already specified.
      */
    if (otype == NULL && out != NULL) {
        otype = PyArray_DESCR(out);
        Py_INCREF(otype);
    }
    if (otype == NULL) {
        /*
         * For integer types --- make sure at least a long
         * is used for add and multiply reduction to avoid overflow
         */
        int typenum = PyArray_TYPE(mp);
        if ((PyTypeNum_ISBOOL(typenum) || PyTypeNum_ISINTEGER(typenum))
            && ((strcmp(ufunc->name,"add") == 0)
                || (strcmp(ufunc->name,"multiply") == 0))) {
            if (PyTypeNum_ISBOOL(typenum)) {
                typenum = NPY_LONG;
            }
            else if ((size_t)PyArray_DESCR(mp)->elsize < sizeof(long)) {
                if (PyTypeNum_ISUNSIGNED(typenum)) {
                    typenum = NPY_ULONG;
                }
                else {
                    typenum = NPY_LONG;
                }
            }
        }
        otype = PyArray_DescrFromType(typenum);
    }


    switch(operation) {
    case UFUNC_REDUCE:
        ret = PyUFunc_Reduce(ufunc, mp, out, naxes, axes,
                             otype, keepdims, initial, wheremask);
        Py_XDECREF(wheremask);
        break;
    case UFUNC_ACCUMULATE:
        if (ndim == 0) {
            PyErr_SetString(PyExc_TypeError, "cannot accumulate on a scalar");
            goto fail;
        }
        if (naxes != 1) {
            PyErr_SetString(PyExc_ValueError,
                        "accumulate does not allow multiple axes");
            goto fail;
        }
        ret = (PyArrayObject *)PyUFunc_Accumulate(ufunc, mp, out, axes[0],
                                                  otype->type_num);
        break;
    case UFUNC_REDUCEAT:
        if (ndim == 0) {
            PyErr_SetString(PyExc_TypeError, "cannot reduceat on a scalar");
            goto fail;
        }
        if (naxes != 1) {
            PyErr_SetString(PyExc_ValueError,
                        "reduceat does not allow multiple axes");
            goto fail;
        }
        ret = (PyArrayObject *)PyUFunc_Reduceat(ufunc, mp, indices, out,
                                            axes[0], otype->type_num);
        Py_DECREF(indices);
        break;
    }
    Py_DECREF(mp);
    Py_DECREF(otype);

    if (ret == NULL) {
        return NULL;
    }

    /* Wrap and return the output */
    {
        /* Find __array_wrap__ - note that these rules are different to the
         * normal ufunc path
         */
        PyObject *wrap;
        if (out != NULL) {
            wrap = Py_None;
            Py_INCREF(wrap);
        }
        else if (Py_TYPE(op) != Py_TYPE(ret)) {
            wrap = PyObject_GetAttr(op, npy_um_str_array_wrap);
            if (wrap == NULL) {
                PyErr_Clear();
            }
            else if (!PyCallable_Check(wrap)) {
                Py_DECREF(wrap);
                wrap = NULL;
            }
        }
        else {
            wrap = NULL;
        }
        return _apply_array_wrap(wrap, ret, NULL);
    }

fail:
    Py_XDECREF(otype);
    Py_XDECREF(mp);
    Py_XDECREF(wheremask);
    return NULL;
}