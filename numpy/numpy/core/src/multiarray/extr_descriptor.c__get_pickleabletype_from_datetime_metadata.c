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
struct TYPE_7__ {size_t base; int num; } ;
struct TYPE_6__ {int /*<<< orphan*/ * metadata; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  TYPE_2__ PyArray_DatetimeMetaData ;

/* Variables and functions */
 int /*<<< orphan*/ * PyBytes_FromString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/ * PyInt_FromLong (int) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SET_ITEM (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _datetime_strings ; 
 TYPE_2__* get_datetime_metadata_from_dtype (TYPE_1__*) ; 

__attribute__((used)) static PyObject *
_get_pickleabletype_from_datetime_metadata(PyArray_Descr *dtype)
{
    PyObject *ret, *dt_tuple;
    PyArray_DatetimeMetaData *meta;

    /* Create the 2-item tuple to return */
    ret = PyTuple_New(2);
    if (ret == NULL) {
        return NULL;
    }

    /* Store the metadata dictionary */
    if (dtype->metadata != NULL) {
        Py_INCREF(dtype->metadata);
        PyTuple_SET_ITEM(ret, 0, dtype->metadata);
    } else {
        PyTuple_SET_ITEM(ret, 0, PyDict_New());
    }

    /* Convert the datetime metadata into a tuple */
    meta = get_datetime_metadata_from_dtype(dtype);
    if (meta == NULL) {
        Py_DECREF(ret);
        return NULL;
    }
    /* Use a 4-tuple that numpy 1.6 knows how to unpickle */
    dt_tuple = PyTuple_New(4);
    if (dt_tuple == NULL) {
        Py_DECREF(ret);
        return NULL;
    }
    PyTuple_SET_ITEM(dt_tuple, 0,
            PyBytes_FromString(_datetime_strings[meta->base]));
    PyTuple_SET_ITEM(dt_tuple, 1,
            PyInt_FromLong(meta->num));
    PyTuple_SET_ITEM(dt_tuple, 2,
            PyInt_FromLong(1));
    PyTuple_SET_ITEM(dt_tuple, 3,
            PyInt_FromLong(1));

    PyTuple_SET_ITEM(ret, 1, dt_tuple);

    return ret;
}