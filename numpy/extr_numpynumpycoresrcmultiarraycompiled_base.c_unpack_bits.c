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
typedef  int npy_uint64 ;
typedef  int npy_intp ;
struct TYPE_3__ {int member_1; int* ptr; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Dims ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_BEGIN_THREADS_DEF ; 
 int /*<<< orphan*/  NPY_BEGIN_THREADS_THRESHOLDED (int) ; 
 int /*<<< orphan*/  NPY_CORDER ; 
 int /*<<< orphan*/  NPY_END_THREADS ; 
 int NPY_MAXDIMS ; 
 scalar_t__ NPY_UBYTE ; 
 scalar_t__ PyArray_CheckAxis (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyArray_DescrFromType (scalar_t__) ; 
 scalar_t__ PyArray_FROM_O (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ISFORTRAN (int /*<<< orphan*/ *) ; 
 void* PyArray_ITER_DATA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ITER_NEXT (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ITER_NOTDONE (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_IterAllButAxis (int /*<<< orphan*/ *,int*) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NewFromDescr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_Newshape (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int PyArray_PyIntAsIntp (int /*<<< orphan*/ *) ; 
 int PyArray_STRIDE (int /*<<< orphan*/ *,int) ; 
 int PyArray_Size (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 scalar_t__ error_converting (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int npy_bswap8 (int) ; 

__attribute__((used)) static PyObject *
unpack_bits(PyObject *input, int axis, PyObject *count_obj)
{
    static int unpack_init = 0;
    static char unpack_lookup[256][8];
    PyArrayObject *inp;
    PyArrayObject *new = NULL;
    PyArrayObject *out = NULL;
    npy_intp outdims[NPY_MAXDIMS];
    int i;
    PyArrayIterObject *it, *ot;
    npy_intp count, in_n, in_tail, out_pad, in_stride, out_stride;
    NPY_BEGIN_THREADS_DEF;

    inp = (PyArrayObject *)PyArray_FROM_O(input);

    if (inp == NULL) {
        return NULL;
    }
    if (PyArray_TYPE(inp) != NPY_UBYTE) {
        PyErr_SetString(PyExc_TypeError,
                "Expected an input array of unsigned byte data type");
        Py_DECREF(inp);
        goto fail;
    }

    new = (PyArrayObject *)PyArray_CheckAxis(inp, &axis, 0);
    Py_DECREF(inp);
    if (new == NULL) {
        return NULL;
    }

    if (PyArray_NDIM(new) == 0) {
        /* Handle 0-d array by converting it to a 1-d array */
        PyArrayObject *temp;
        PyArray_Dims newdim = {NULL, 1};
        npy_intp shape = 1;

        newdim.ptr = &shape;
        temp = (PyArrayObject *)PyArray_Newshape(new, &newdim, NPY_CORDER);
        Py_DECREF(new);
        if (temp == NULL) {
            return NULL;
        }
        new = temp;
    }

    /* Setup output shape */
    for (i = 0; i < PyArray_NDIM(new); i++) {
        outdims[i] = PyArray_DIM(new, i);
    }

    /* Multiply axis dimension by 8 */
    outdims[axis] *= 8;
    if (count_obj != Py_None) {
        count = PyArray_PyIntAsIntp(count_obj);
        if (error_converting(count)) {
            goto fail;
        }
        if (count < 0) {
            outdims[axis] += count;
            if (outdims[axis] < 0) {
                PyErr_Format(PyExc_ValueError,
                             "-count larger than number of elements");
                goto fail;
            }
        }
        else {
            outdims[axis] = count;
        }
    }

    /* Create output array */
    out = (PyArrayObject *)PyArray_NewFromDescr(
            Py_TYPE(new), PyArray_DescrFromType(NPY_UBYTE),
            PyArray_NDIM(new), outdims, NULL, NULL,
            PyArray_ISFORTRAN(new), NULL);
    if (out == NULL) {
        goto fail;
    }

    /* Setup iterators to iterate over all but given axis */
    it = (PyArrayIterObject *)PyArray_IterAllButAxis((PyObject *)new, &axis);
    ot = (PyArrayIterObject *)PyArray_IterAllButAxis((PyObject *)out, &axis);
    if (it == NULL || ot == NULL) {
        Py_XDECREF(it);
        Py_XDECREF(ot);
        goto fail;
    }

    /* setup lookup table under GIL, big endian 0..256 as bytes */
    if (unpack_init == 0) {
        npy_uint64 j;
        npy_uint64 * unpack_lookup_64 = (npy_uint64 *)unpack_lookup;
        for (j=0; j < 256; j++) {
            npy_uint64 v = 0;
            v |= (npy_uint64)((j &   1) ==   1);
            v |= (npy_uint64)((j &   2) ==   2) << 8;
            v |= (npy_uint64)((j &   4) ==   4) << 16;
            v |= (npy_uint64)((j &   8) ==   8) << 24;
            v |= (npy_uint64)((j &  16) ==  16) << 32;
            v |= (npy_uint64)((j &  32) ==  32) << 40;
            v |= (npy_uint64)((j &  64) ==  64) << 48;
            v |= (npy_uint64)((j & 128) == 128) << 56;
#if NPY_BYTE_ORDER == NPY_LITTLE_ENDIAN
            v = npy_bswap8(v);
#endif
            unpack_lookup_64[j] = v;
        }
        unpack_init = 1;
    }

    count = PyArray_DIM(new, axis) * 8;
    if (outdims[axis] > count) {
        in_n = count / 8;
        in_tail = 0;
        out_pad = outdims[axis] - count;
    }
    else {
        in_n = outdims[axis] / 8;
        in_tail = outdims[axis] % 8;
        out_pad = 0;
    }

    in_stride = PyArray_STRIDE(new, axis);
    out_stride = PyArray_STRIDE(out, axis);

    NPY_BEGIN_THREADS_THRESHOLDED(PyArray_Size((PyObject *)out) / 8);

    while (PyArray_ITER_NOTDONE(it)) {
        npy_intp index;
        unsigned const char *inptr = PyArray_ITER_DATA(it);
        char *outptr = PyArray_ITER_DATA(ot);

        if (out_stride == 1) {
            /* for unity stride we can just copy out of the lookup table */
            for (index = 0; index < in_n; index++) {
                memcpy(outptr, unpack_lookup[*inptr], 8);
                outptr += 8;
                inptr += in_stride;
            }
            /* Clean up the tail portion */
            if (in_tail) {
                memcpy(outptr, unpack_lookup[*inptr], in_tail);
            }
            /* Add padding */
            else if (out_pad) {
                memset(outptr, 0, out_pad);
            }
        }
        else {
            unsigned char mask;

            for (index = 0; index < in_n; index++) {
                for (mask = 128; mask; mask >>= 1) {
                    *outptr = ((mask & (*inptr)) != 0);
                    outptr += out_stride;
                }
                inptr += in_stride;
            }
            /* Clean up the tail portion */
            mask = 128;
            for (i = 0; i < in_tail; i++) {
                *outptr = ((mask & (*inptr)) != 0);
                outptr += out_stride;
                mask >>= 1;
            }
            /* Add padding */
            for (index = 0; index < out_pad; index++) {
                *outptr = 0;
                outptr += out_stride;
            }
        }
        PyArray_ITER_NEXT(it);
        PyArray_ITER_NEXT(ot);
    }
    NPY_END_THREADS;

    Py_DECREF(it);
    Py_DECREF(ot);

    Py_DECREF(new);
    return (PyObject *)out;

fail:
    Py_XDECREF(new);
    Py_XDECREF(out);
    return NULL;
}