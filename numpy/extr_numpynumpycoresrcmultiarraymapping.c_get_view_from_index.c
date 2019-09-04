#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_intp ;
struct TYPE_3__ {int type; int value; int /*<<< orphan*/  object; } ;
typedef  TYPE_1__ npy_index_info ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
#define  HAS_0D_BOOL 132 
#define  HAS_ELLIPSIS 131 
#define  HAS_INTEGER 130 
#define  HAS_NEWAXIS 129 
#define  HAS_SLICE 128 
 int NPY_MAXDIMS ; 
 int /*<<< orphan*/  NpySlice_GetIndicesEx (int /*<<< orphan*/ ,int,int*,int*,int*,int*) ; 
 char* PyArray_BYTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int* PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NewFromDescrAndBase (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,int*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PyArray_STRIDE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Py_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_and_adjust_index (int*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_view_from_index(PyArrayObject *self, PyArrayObject **view,
                    npy_index_info *indices, int index_num, int ensure_array) {
    npy_intp new_strides[NPY_MAXDIMS];
    npy_intp new_shape[NPY_MAXDIMS];
    int i, j;
    int new_dim = 0;
    int orig_dim = 0;
    char *data_ptr = PyArray_BYTES(self);

    /* for slice parsing */
    npy_intp start, stop, step, n_steps;

    for (i=0; i < index_num; i++) {
        switch (indices[i].type) {
            case HAS_INTEGER:
                if ((check_and_adjust_index(&indices[i].value,
                                PyArray_DIMS(self)[orig_dim], orig_dim,
                                NULL)) < 0) {
                    return -1;
                }
                data_ptr += PyArray_STRIDE(self, orig_dim) * indices[i].value;

                new_dim += 0;
                orig_dim += 1;
                break;
            case HAS_ELLIPSIS:
                for (j=0; j < indices[i].value; j++) {
                    new_strides[new_dim] = PyArray_STRIDE(self, orig_dim);
                    new_shape[new_dim] = PyArray_DIMS(self)[orig_dim];
                    new_dim += 1;
                    orig_dim += 1;
                }
                break;
            case HAS_SLICE:
                if (NpySlice_GetIndicesEx(indices[i].object,
                                          PyArray_DIMS(self)[orig_dim],
                                          &start, &stop, &step, &n_steps) < 0) {
                    return -1;
                }
                if (n_steps <= 0) {
                    /* TODO: Always points to start then, could change that */
                    n_steps = 0;
                    step = 1;
                    start = 0;
                }

                data_ptr += PyArray_STRIDE(self, orig_dim) * start;
                new_strides[new_dim] = PyArray_STRIDE(self, orig_dim) * step;
                new_shape[new_dim] = n_steps;
                new_dim += 1;
                orig_dim += 1;
                break;
            case HAS_NEWAXIS:
                new_strides[new_dim] = 0;
                new_shape[new_dim] = 1;
                new_dim += 1;
                break;
            /* Fancy and 0-d boolean indices are ignored here */
            case HAS_0D_BOOL:
                break;
            default:
                new_dim += 0;
                orig_dim += 1;
                break;
        }
    }

    /* Create the new view and set the base array */
    Py_INCREF(PyArray_DESCR(self));
    *view = (PyArrayObject *)PyArray_NewFromDescrAndBase(
            ensure_array ? &PyArray_Type : Py_TYPE(self),
            PyArray_DESCR(self),
            new_dim, new_shape, new_strides, data_ptr,
            PyArray_FLAGS(self),
            ensure_array ? NULL : (PyObject *)self,
            (PyObject *)self);
    if (*view == NULL) {
        return -1;
    }

    return 0;
}