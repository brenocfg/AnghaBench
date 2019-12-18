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
typedef  scalar_t__ npy_intp ;
typedef  int NPY_CLIPMODE ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_BEGIN_ALLOW_THREADS ; 
#define  NPY_CLIP 130 
 int /*<<< orphan*/  NPY_END_ALLOW_THREADS ; 
 int NPY_FAIL ; 
#define  NPY_RAISE 129 
 int NPY_SUCCEED ; 
#define  NPY_WRAP 128 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 

__attribute__((used)) static int
ravel_multi_index_loop(int ravel_ndim, npy_intp *ravel_dims,
                        npy_intp *ravel_strides,
                        npy_intp count,
                        NPY_CLIPMODE *modes,
                        char **coords, npy_intp *coords_strides)
{
    int i;
    char invalid;
    npy_intp j, m;

    /*
     * Check for 0-dimensional axes unless there is nothing to do.
     * An empty array/shape cannot be indexed at all.
     */
    if (count != 0) {
        for (i = 0; i < ravel_ndim; ++i) {
            if (ravel_dims[i] == 0) {
                PyErr_SetString(PyExc_ValueError,
                        "cannot unravel if shape has zero entries (is empty).");
                return NPY_FAIL;
            }
        }
    }

    NPY_BEGIN_ALLOW_THREADS;
    invalid = 0;
    while (count--) {
        npy_intp raveled = 0;
        for (i = 0; i < ravel_ndim; ++i) {
            m = ravel_dims[i];
            j = *(npy_intp *)coords[i];
            switch (modes[i]) {
                case NPY_RAISE:
                    if (j < 0 || j >= m) {
                        invalid = 1;
                        goto end_while;
                    }
                    break;
                case NPY_WRAP:
                    if (j < 0) {
                        j += m;
                        if (j < 0) {
                            j = j % m;
                            if (j != 0) {
                                j += m;
                            }
                        }
                    }
                    else if (j >= m) {
                        j -= m;
                        if (j >= m) {
                            j = j % m;
                        }
                    }
                    break;
                case NPY_CLIP:
                    if (j < 0) {
                        j = 0;
                    }
                    else if (j >= m) {
                        j = m - 1;
                    }
                    break;

            }
            raveled += j * ravel_strides[i];

            coords[i] += coords_strides[i];
        }
        *(npy_intp *)coords[ravel_ndim] = raveled;
        coords[ravel_ndim] += coords_strides[ravel_ndim];
    }
end_while:
    NPY_END_ALLOW_THREADS;
    if (invalid) {
        PyErr_SetString(PyExc_ValueError,
              "invalid entry in coordinates array");
        return NPY_FAIL;
    }
    return NPY_SUCCEED;
}