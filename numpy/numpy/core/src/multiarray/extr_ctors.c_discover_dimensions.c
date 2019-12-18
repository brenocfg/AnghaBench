#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_intp ;
struct TYPE_7__ {int two; int nd; int* shape; } ;
struct TYPE_6__ {int ndim; int* shape; int len; } ;
typedef  TYPE_1__ Py_buffer ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  TYPE_2__ PyArrayInterface ;

/* Variables and functions */
 int /*<<< orphan*/  Generic ; 
 int NPY_MAXDIMS ; 
 scalar_t__ NpyCapsule_AsVoidPtr (int /*<<< orphan*/ *) ; 
 scalar_t__ NpyCapsule_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_Check (int /*<<< orphan*/ *) ; 
 int PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 scalar_t__ PyArray_IsScalar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyArray_LookupSpecial_OnInstance (int /*<<< orphan*/ *,char*) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int PyBUF_ND ; 
 int PyBUF_SIMPLE ; 
 int PyBUF_STRIDES ; 
 scalar_t__ PyBuffer_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyBuffer_Release (TYPE_1__*) ; 
 scalar_t__ PyDict_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyErr_Clear () ; 
 scalar_t__ PyErr_ExceptionMatches (int /*<<< orphan*/ ) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_BufferError ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int PyInt_AsSsize_t (int /*<<< orphan*/ ) ; 
 int PyObject_CheckBuffer (int /*<<< orphan*/ *) ; 
 scalar_t__ PyObject_GetBuffer (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  PySequence_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_Fast (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PySequence_Fast_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PySequence_Fast_GET_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ PySequence_Length (int /*<<< orphan*/ *) ; 
 scalar_t__ PyString_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dealloc_cached_buffer_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
discover_dimensions(PyObject *obj, int *maxndim, npy_intp *d, int check_it,
                                    int stop_at_string, int stop_at_tuple,
                                    int *out_is_object)
{
    PyObject *e;
    npy_intp n, i;
    Py_buffer buffer_view;
    PyObject * seq;

    if (*maxndim == 0) {
        return 0;
    }

    /* obj is an Array */
    if (PyArray_Check(obj)) {
        PyArrayObject *arr = (PyArrayObject *)obj;

        if (PyArray_NDIM(arr) < *maxndim) {
            *maxndim = PyArray_NDIM(arr);
        }

        for (i=0; i<*maxndim; i++) {
            d[i] = PyArray_DIM(arr,i);
        }
        return 0;
    }

    /* obj is a Scalar */
    if (PyArray_IsScalar(obj, Generic)) {
        *maxndim = 0;
        return 0;
    }

    /* obj is not a Sequence */
    if (!PySequence_Check(obj) ||
            PySequence_Length(obj) < 0) {
        *maxndim = 0;
        PyErr_Clear();
        return 0;
    }

    /* obj is a String */
    if (PyString_Check(obj) ||
#if defined(NPY_PY3K)
#else
            PyBuffer_Check(obj) ||
#endif
            PyUnicode_Check(obj)) {
        if (stop_at_string) {
            *maxndim = 0;
        }
        else {
            d[0] = PySequence_Length(obj);
            *maxndim = 1;
        }
        return 0;
    }

    /* obj is a Tuple, but tuples aren't expanded */
    if (stop_at_tuple && PyTuple_Check(obj)) {
        *maxndim = 0;
        return 0;
    }

    /* obj is a PEP 3118 buffer */
    /* PEP 3118 buffer interface */
    if (PyObject_CheckBuffer(obj) == 1) {
        memset(&buffer_view, 0, sizeof(Py_buffer));
        if (PyObject_GetBuffer(obj, &buffer_view,
                    PyBUF_STRIDES|PyBUF_SIMPLE) == 0 ||
                PyObject_GetBuffer(obj, &buffer_view,
                    PyBUF_ND|PyBUF_SIMPLE) == 0) {
            int nd = buffer_view.ndim;

            if (nd < *maxndim) {
                *maxndim = nd;
            }
            for (i = 0; i < *maxndim; i++) {
                d[i] = buffer_view.shape[i];
            }
            PyBuffer_Release(&buffer_view);
            _dealloc_cached_buffer_info(obj);
            return 0;
        }
        else if (PyErr_Occurred()) {
            if (PyErr_ExceptionMatches(PyExc_BufferError) ||
                    PyErr_ExceptionMatches(PyExc_TypeError)) {
                PyErr_Clear();
            } else {
                return -1;
            }
        }
        else if (PyObject_GetBuffer(obj, &buffer_view, PyBUF_SIMPLE) == 0) {
            d[0] = buffer_view.len;
            *maxndim = 1;
            PyBuffer_Release(&buffer_view);
            _dealloc_cached_buffer_info(obj);
            return 0;
        }
        else if (PyErr_Occurred()) {
            if (PyErr_ExceptionMatches(PyExc_BufferError) ||
                    PyErr_ExceptionMatches(PyExc_TypeError)) {
                PyErr_Clear();
            } else {
                return -1;
            }
        }
    }

    /* obj has the __array_struct__ interface */
    e = PyArray_LookupSpecial_OnInstance(obj, "__array_struct__");
    if (e != NULL) {
        int nd = -1;

        if (NpyCapsule_Check(e)) {
            PyArrayInterface *inter;
            inter = (PyArrayInterface *)NpyCapsule_AsVoidPtr(e);
            if (inter->two == 2) {
                nd = inter->nd;
                if (nd >= 0) {
                    if (nd < *maxndim) {
                        *maxndim = nd;
                    }
                    for (i=0; i<*maxndim; i++) {
                        d[i] = inter->shape[i];
                    }
                }
            }
        }
        Py_DECREF(e);
        if (nd >= 0) {
            return 0;
        }
    }
    else if (PyErr_Occurred()) {
        PyErr_Clear(); /* TODO[gh-14801]: propagate crashes during attribute access? */
    }


    /* obj has the __array_interface__ interface */
    e = PyArray_LookupSpecial_OnInstance(obj, "__array_interface__");
    if (e != NULL) {
        int nd = -1;
        if (PyDict_Check(e)) {
            PyObject *new;
            new = PyDict_GetItemString(e, "shape");
            if (new && PyTuple_Check(new)) {
                nd = PyTuple_GET_SIZE(new);
                if (nd < *maxndim) {
                    *maxndim = nd;
                }
                for (i=0; i<*maxndim; i++) {
                    d[i] = PyInt_AsSsize_t(PyTuple_GET_ITEM(new, i));
                    if (d[i] < 0) {
                        PyErr_SetString(PyExc_RuntimeError,
                                "Invalid shape in __array_interface__");
                        Py_DECREF(e);
                        return -1;
                    }
                }
            }
        }
        Py_DECREF(e);
        if (nd >= 0) {
            return 0;
        }
    }
    else if (PyErr_Occurred()) {
        PyErr_Clear(); /* TODO[gh-14801]: propagate crashes during attribute access? */
    }

    seq = PySequence_Fast(obj, "Could not convert object to sequence");
    if (seq == NULL) {
        /*
         * PySequence_Check detects whether an old type object is a
         * sequence by the presence of the __getitem__ attribute, and
         * for new type objects that aren't dictionaries by the
         * presence of the __len__ attribute as well. In either case it
         * is possible to have an object that tests as a sequence but
         * doesn't behave as a sequence and consequently, the
         * PySequence_GetItem call can fail. When that happens and the
         * object looks like a dictionary, we truncate the dimensions
         * and set the object creation flag, otherwise we pass the
         * error back up the call chain.
         */
        if (PyErr_ExceptionMatches(PyExc_KeyError)) {
            PyErr_Clear();
            *maxndim = 0;
            *out_is_object = 1;
            return 0;
        }
        else {
            return -1;
        }
    }
    n = PySequence_Fast_GET_SIZE(seq);

    d[0] = n;

    /* 1-dimensional sequence */
    if (n == 0 || *maxndim == 1) {
        *maxndim = 1;
        Py_DECREF(seq);
        return 0;
    }
    else {
        int all_elems_maxndim = *maxndim - 1;
        npy_intp *all_elems_d = d + 1;
        int all_dimensions_match = 1;

        /* Get the dimensions of the first item as a baseline */
        PyObject *first = PySequence_Fast_GET_ITEM(seq, 0);
        if (discover_dimensions(
                first, &all_elems_maxndim, all_elems_d, check_it,
                stop_at_string, stop_at_tuple, out_is_object) < 0) {
            Py_DECREF(seq);
            return -1;
        }

        /* Compare the dimensions of all the remaining items */
        for (i = 1; i < n; ++i) {
            int j;
            int elem_maxndim = *maxndim - 1;
            npy_intp elem_d[NPY_MAXDIMS];

            PyObject *elem = PySequence_Fast_GET_ITEM(seq, i);
            if (discover_dimensions(
                    elem, &elem_maxndim, elem_d, check_it,
                    stop_at_string, stop_at_tuple, out_is_object) < 0) {
                Py_DECREF(seq);
                return -1;
            }

            /* Find the number of left-dimensions which match, j */
            for (j = 0; j < elem_maxndim && j < all_elems_maxndim; ++j) {
                if (elem_d[j] != all_elems_d[j]) {
                    break;
                }
            }
            if (j != elem_maxndim || j != all_elems_maxndim) {
                all_dimensions_match = 0;
            }
            all_elems_maxndim = j;
        }
        *maxndim = all_elems_maxndim + 1;
        if (!all_dimensions_match) {
            /* typically results in an array containing variable-length lists */
            *out_is_object = 1;
        }
    }

    Py_DECREF(seq);

    return 0;
}