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
typedef  int npy_intp ;
struct TYPE_5__ {int type; int value; scalar_t__ object; } ;
typedef  TYPE_1__ npy_index_info ;
struct TYPE_6__ {int nd_fancy; int* dimensions; int consec; int* fancy_dims; int* iteraxes; int /*<<< orphan*/ * subspace; scalar_t__* fancy_strides; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  TYPE_2__ PyArrayMapIterObject ;

/* Variables and functions */
 int HAS_0D_BOOL ; 
 int HAS_ELLIPSIS ; 
 int HAS_FANCY ; 
 int HAS_INTEGER ; 
 int HAS_NEWAXIS ; 
 void* PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_SHAPE (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_STRIDE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyExc_IndexError ; 
 int /*<<< orphan*/  PyUString_ConcatAndDel (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUString_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * convert_shape_to_string (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
mapiter_fill_info(PyArrayMapIterObject *mit, npy_index_info *indices,
                  int index_num, PyArrayObject *arr)
{
    int j = 0, i;
    int curr_dim = 0;
     /* dimension of index result (up to first fancy index) */
    int result_dim = 0;
    /* -1 init; 0 found fancy; 1 fancy stopped; 2 found not consecutive fancy */
    int consec_status = -1;
    int axis, broadcast_axis;
    npy_intp dimension;
    PyObject *errmsg, *tmp;

    for (i = 0; i < mit->nd_fancy; i++) {
        mit->dimensions[i] = 1;
    }

    mit->consec = 0;
    for (i = 0; i < index_num; i++) {
        /* integer and fancy indexes are transposed together */
        if (indices[i].type & (HAS_FANCY | HAS_INTEGER)) {
            /* there was no previous fancy index, so set consec */
            if (consec_status == -1) {
                mit->consec = result_dim;
                consec_status = 0;
            }
            /* there was already a non-fancy index after a fancy one */
            else if (consec_status == 1) {
                consec_status = 2;
                mit->consec = 0;
            }
        }
        else {
            /* consec_status == 0 means there was a fancy index before */
            if (consec_status == 0) {
                consec_status = 1;
            }
        }

        /* (iterating) fancy index, store the iterator */
        if (indices[i].type == HAS_FANCY) {
            mit->fancy_strides[j] = PyArray_STRIDE(arr, curr_dim);
            mit->fancy_dims[j] = PyArray_DIM(arr, curr_dim);
            mit->iteraxes[j++] = curr_dim++;

            /* Check broadcasting */
            broadcast_axis = mit->nd_fancy;
            /* Fill from back, we know how many dims there are */
            for (axis = PyArray_NDIM((PyArrayObject *)indices[i].object) - 1;
                        axis >= 0; axis--) {
                broadcast_axis--;
                dimension = PyArray_DIM((PyArrayObject *)indices[i].object, axis);

                /* If it is 1, we can broadcast */
                if (dimension != 1) {
                    if (dimension != mit->dimensions[broadcast_axis]) {
                        if (mit->dimensions[broadcast_axis] != 1) {
                            goto broadcast_error;
                        }
                        mit->dimensions[broadcast_axis] = dimension;
                    }
                }
            }
        }
        else if (indices[i].type == HAS_0D_BOOL) {
            mit->fancy_strides[j] = 0;
            mit->fancy_dims[j] = 1;
            /* Does not exist */
            mit->iteraxes[j++] = -1;
            if ((indices[i].value == 0) &&
                    (mit->dimensions[mit->nd_fancy - 1]) > 1) {
                goto broadcast_error;
            }
            mit->dimensions[mit->nd_fancy-1] *= indices[i].value;
        }

        /* advance curr_dim for non-fancy indices */
        else if (indices[i].type == HAS_ELLIPSIS) {
            curr_dim += (int)indices[i].value;
            result_dim += (int)indices[i].value;
        }
        else if (indices[i].type != HAS_NEWAXIS){
            curr_dim += 1;
            result_dim += 1;
        }
        else {
            result_dim += 1;
        }
    }

    /* Fill dimension of subspace */
    if (mit->subspace) {
        for (i = 0; i < PyArray_NDIM(mit->subspace); i++) {
            mit->dimensions[mit->nd_fancy + i] = PyArray_DIM(mit->subspace, i);
        }
    }

    return 0;

  broadcast_error:
    /*
     * Attempt to set a meaningful exception. Could also find out
     * if a boolean index was converted.
     */
    errmsg = PyUString_FromString("shape mismatch: indexing arrays could not "
                                  "be broadcast together with shapes ");
    if (errmsg == NULL) {
        return -1;
    }

    for (i = 0; i < index_num; i++) {
        if (!(indices[i].type & HAS_FANCY)) {
            continue;
        }
        tmp = convert_shape_to_string(
                    PyArray_NDIM((PyArrayObject *)indices[i].object),
                    PyArray_SHAPE((PyArrayObject *)indices[i].object),
                    " ");
        if (tmp == NULL) {
            return -1;
        }
        PyUString_ConcatAndDel(&errmsg, tmp);
        if (errmsg == NULL) {
            return -1;
        }
    }

    PyErr_SetObject(PyExc_IndexError, errmsg);
    Py_DECREF(errmsg);
    return -1;
}