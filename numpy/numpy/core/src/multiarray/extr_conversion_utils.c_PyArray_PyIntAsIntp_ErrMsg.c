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
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  Bool ; 
 long NPY_MAX_INTP ; 
 long NPY_MIN_INTP ; 
 scalar_t__ PyArray_IsScalar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PyBool_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_GivenExceptionMatches (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  PyExc_OverflowError ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int PyInt_AS_LONG (int /*<<< orphan*/ *) ; 
 scalar_t__ PyInt_CheckExact (int /*<<< orphan*/ *) ; 
 long PyLong_AsLong (int /*<<< orphan*/ *) ; 
 long PyLong_AsLongLong (int /*<<< orphan*/ *) ; 
 scalar_t__ PyLong_CheckExact (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyNumber_Index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ error_converting (long) ; 

__attribute__((used)) static npy_intp
PyArray_PyIntAsIntp_ErrMsg(PyObject *o, const char * msg)
{
#if (NPY_SIZEOF_LONG < NPY_SIZEOF_INTP)
    long long long_value = -1;
#else
    long long_value = -1;
#endif
    PyObject *obj, *err;

    /*
     * Be a bit stricter and not allow bools.
     * np.bool_ is also disallowed as Boolean arrays do not currently
     * support index.
     */
    if (!o || PyBool_Check(o) || PyArray_IsScalar(o, Bool)) {
        PyErr_SetString(PyExc_TypeError, msg);
        return -1;
    }

    /*
     * Since it is the usual case, first check if o is an integer. This is
     * an exact check, since otherwise __index__ is used.
     */
#if !defined(NPY_PY3K)
    if (PyInt_CheckExact(o)) {
  #if (NPY_SIZEOF_LONG <= NPY_SIZEOF_INTP)
        /* No overflow is possible, so we can just return */
        return PyInt_AS_LONG(o);
  #else
        long_value = PyInt_AS_LONG(o);
        goto overflow_check;
  #endif
    }
    else
#endif
    if (PyLong_CheckExact(o)) {
#if (NPY_SIZEOF_LONG < NPY_SIZEOF_INTP)
        long_value = PyLong_AsLongLong(o);
#else
        long_value = PyLong_AsLong(o);
#endif
        return (npy_intp)long_value;
    }

    /*
     * The most general case. PyNumber_Index(o) covers everything
     * including arrays. In principle it may be possible to replace
     * the whole function by PyIndex_AsSSize_t after deprecation.
     */
    obj = PyNumber_Index(o);
    if (obj == NULL) {
        return -1;
    }
#if (NPY_SIZEOF_LONG < NPY_SIZEOF_INTP)
    long_value = PyLong_AsLongLong(obj);
#else
    long_value = PyLong_AsLong(obj);
#endif
    Py_DECREF(obj);

    if (error_converting(long_value)) {
        err = PyErr_Occurred();
        /* Only replace TypeError's here, which are the normal errors. */
        if (PyErr_GivenExceptionMatches(err, PyExc_TypeError)) {
            PyErr_SetString(PyExc_TypeError, msg);
        }
        return -1;
    }
    goto overflow_check; /* silence unused warning */

overflow_check:
#if (NPY_SIZEOF_LONG < NPY_SIZEOF_INTP)
  #if (NPY_SIZEOF_LONGLONG > NPY_SIZEOF_INTP)
    if ((long_value < NPY_MIN_INTP) || (long_value > NPY_MAX_INTP)) {
        PyErr_SetString(PyExc_OverflowError,
                "Python int too large to convert to C numpy.intp");
        return -1;
    }
  #endif
#else
  #if (NPY_SIZEOF_LONG > NPY_SIZEOF_INTP)
    if ((long_value < NPY_MIN_INTP) || (long_value > NPY_MAX_INTP)) {
        PyErr_SetString(PyExc_OverflowError,
                "Python int too large to convert to C numpy.intp");
        return -1;
    }
  #endif
#endif
    return long_value;
}