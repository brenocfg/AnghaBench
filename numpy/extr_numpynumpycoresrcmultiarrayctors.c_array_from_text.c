#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* skip_separator ) (void**,char*,void*) ;
typedef  scalar_t__ npy_intp ;
typedef  scalar_t__ (* next_element ) (void**,char*,TYPE_1__*,void*) ;
struct TYPE_14__ {char* data; } ;
struct TYPE_13__ {scalar_t__ elsize; } ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  TYPE_3__ PyArrayObject_fields ;
typedef  TYPE_1__ PyArrayObject ;

/* Variables and functions */
 scalar_t__ FROM_BUFFER_SIZE ; 
 int /*<<< orphan*/  NPY_BEGIN_ALLOW_THREADS ; 
 int /*<<< orphan*/  NPY_END_ALLOW_THREADS ; 
 char* PyArray_DATA (TYPE_1__*) ; 
 size_t* PyArray_DIMS (TYPE_1__*) ; 
 scalar_t__ PyArray_MAX (size_t,int) ; 
 scalar_t__ PyArray_NewFromDescr (int /*<<< orphan*/ *,TYPE_1__*,int,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 char* PyDataMem_RENEW (char*,scalar_t__) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* swab_separator (char*) ; 

__attribute__((used)) static PyArrayObject *
array_from_text(PyArray_Descr *dtype, npy_intp num, char *sep, size_t *nread,
                void *stream, next_element next, skip_separator skip_sep,
                void *stream_data)
{
    PyArrayObject *r;
    npy_intp i;
    char *dptr, *clean_sep, *tmp;
    int err = 0;
    npy_intp thisbuf = 0;
    npy_intp size;
    npy_intp bytes, totalbytes;

    size = (num >= 0) ? num : FROM_BUFFER_SIZE;

    /*
     * When dtype->subarray is true, PyArray_NewFromDescr will decref dtype
     * even on success, so make sure it stays around until exit.
     */
    Py_INCREF(dtype);
    r = (PyArrayObject *)
        PyArray_NewFromDescr(&PyArray_Type, dtype, 1, &size,
                             NULL, NULL, 0, NULL);
    if (r == NULL) {
        Py_DECREF(dtype);
        return NULL;
    }
    clean_sep = swab_separator(sep);
    if (clean_sep == NULL) {
        err = 1;
        goto fail;
    }

    NPY_BEGIN_ALLOW_THREADS;
    totalbytes = bytes = size * dtype->elsize;
    dptr = PyArray_DATA(r);
    for (i= 0; num < 0 || i < num; i++) {
        if (next(&stream, dptr, dtype, stream_data) < 0) {
            /* EOF */
            break;
        }
        *nread += 1;
        thisbuf += 1;
        dptr += dtype->elsize;
        if (num < 0 && thisbuf == size) {
            totalbytes += bytes;
            tmp = PyDataMem_RENEW(PyArray_DATA(r), totalbytes);
            if (tmp == NULL) {
                err = 1;
                break;
            }
            ((PyArrayObject_fields *)r)->data = tmp;
            dptr = tmp + (totalbytes - bytes);
            thisbuf = 0;
        }
        if (skip_sep(&stream, clean_sep, stream_data) < 0) {
            break;
        }
    }
    if (num < 0) {
        tmp = PyDataMem_RENEW(PyArray_DATA(r), PyArray_MAX(*nread,1)*dtype->elsize);
        if (tmp == NULL) {
            err = 1;
        }
        else {
            PyArray_DIMS(r)[0] = *nread;
            ((PyArrayObject_fields *)r)->data = tmp;
        }
    }
    NPY_END_ALLOW_THREADS;
    free(clean_sep);

fail:
    Py_DECREF(dtype);
    if (err == 1) {
        PyErr_NoMemory();
    }
    if (PyErr_Occurred()) {
        Py_DECREF(r);
        return NULL;
    }
    return r;
}