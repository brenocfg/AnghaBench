#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type_num; } ;
struct TYPE_5__ {int /*<<< orphan*/  obmeta; } ;
typedef  scalar_t__ Py_ssize_t ;
typedef  TYPE_1__ PyTimedeltaScalarObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArray_DatetimeMetaData ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ NPY_DATETIME ; 
 scalar_t__ NPY_OBJECT ; 
 scalar_t__ NPY_TIMEDELTA ; 
 scalar_t__ Npy_EnterRecursiveCall (char*) ; 
 scalar_t__ PyArray_Check (int /*<<< orphan*/ *) ; 
 TYPE_2__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_IsScalar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyBytes_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyDelta_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/ * PyObject_GetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PySequence_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PySequence_GetItem (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PySequence_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_New (int /*<<< orphan*/ ) ; 
 scalar_t__ PyUnicode_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_LeaveRecursiveCall () ; 
 int /*<<< orphan*/  Timedelta ; 
 scalar_t__ compute_datetime_metadata_greatest_common_divisor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int delta_checker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_datetime_metadata_from_dtype (TYPE_2__*) ; 

__attribute__((used)) static int
recursive_find_object_timedelta64_type(PyObject *obj,
                        PyArray_DatetimeMetaData *meta)
{
    /* Array -> use its metadata */
    if (PyArray_Check(obj)) {
        PyArrayObject *arr = (PyArrayObject *)obj;
        PyArray_Descr *arr_dtype = PyArray_DESCR(arr);

        /* If the array has metadata, use it */
        if (arr_dtype->type_num == NPY_DATETIME ||
                    arr_dtype->type_num == NPY_TIMEDELTA) {
            PyArray_DatetimeMetaData *tmp_meta;

            /* Get the metadata from the type */
            tmp_meta = get_datetime_metadata_from_dtype(arr_dtype);
            if (tmp_meta == NULL) {
                return -1;
            }

            /* Combine it with 'meta' */
            if (compute_datetime_metadata_greatest_common_divisor(meta,
                            tmp_meta, meta, 0, 0) < 0) {
                return -1;
            }

            return 0;
        }
        /* If it's not an object array, stop looking */
        else if (arr_dtype->type_num != NPY_OBJECT) {
            return 0;
        }
        else {
            if (PyArray_NDIM(arr) == 0) {
                /*
                 * special handling of 0 dimensional NumPy object
                 * arrays, which may be indexed to retrieve their
                 * single object using [()], but not by using
                 * __getitem__(integer) approaches
                 */
                PyObject *item, *args;

                args = PyTuple_New(0);
                if (args == NULL) {
                    return 0;
                }
                item = PyObject_GetItem(obj, args);
                Py_DECREF(args);
                if (item == NULL) {
                    return 0;
                }
                /*
                 * NOTE: may need other type checks here in the future
                 * for expanded 0 D datetime array conversions?
                 */
                if (PyDelta_Check(item)) {
                    Py_DECREF(item);
                    return delta_checker(meta);
                }
                Py_DECREF(item);
            }
        }
    }
    /* Datetime scalar -> use its metadata */
    else if (PyArray_IsScalar(obj, Timedelta)) {
        PyTimedeltaScalarObject *dts = (PyTimedeltaScalarObject *)obj;

        /* Combine it with 'meta' */
        if (compute_datetime_metadata_greatest_common_divisor(meta,
                        &dts->obmeta, meta, 1, 1) < 0) {
            return -1;
        }

        return 0;
    }
    /* String -> parse it to find out */
    else if (PyBytes_Check(obj) || PyUnicode_Check(obj)) {
        /* No timedelta parser yet */
        return 0;
    }
    /* Python timedelta object -> 'us' */
    else if (PyDelta_Check(obj)) {
        return delta_checker(meta);
    }

    /* Now check if what we have left is a sequence for recursion */
    if (PySequence_Check(obj)) {
        Py_ssize_t i, len = PySequence_Size(obj);
        if (len < 0 && PyErr_Occurred()) {
            return -1;
        }

        for (i = 0; i < len; ++i) {
            int ret;
            PyObject *f = PySequence_GetItem(obj, i);
            if (f == NULL) {
                return -1;
            }
            if (Npy_EnterRecursiveCall(" in recursive_find_object_timedelta64_type") != 0) {
                Py_DECREF(f);
                return -1;
            }
            ret = recursive_find_object_timedelta64_type(f, meta);
            Py_LeaveRecursiveCall();
            Py_DECREF(f);
            if (ret < 0) {
                return ret;
            }
        }

        return 0;
    }
    /* Otherwise ignore it */
    else {
        return 0;
    }
}