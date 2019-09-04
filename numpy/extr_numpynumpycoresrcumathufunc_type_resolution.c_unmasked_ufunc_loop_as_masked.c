#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ npy_intp ;
struct TYPE_2__ {int nargs; void* unmasked_innerloopdata; int /*<<< orphan*/  (* unmasked_innerloop ) (char**,scalar_t__*,scalar_t__*,void*) ;} ;
typedef  TYPE_1__ _ufunc_masker_data ;
typedef  int /*<<< orphan*/  (* PyUFuncGenericFunction ) (char**,scalar_t__*,scalar_t__*,void*) ;
typedef  int /*<<< orphan*/  NpyAuxData ;

/* Variables and functions */
 char* npy_memchr (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static void
unmasked_ufunc_loop_as_masked(
             char **dataptrs, npy_intp *strides,
             char *mask, npy_intp mask_stride,
             npy_intp loopsize,
             NpyAuxData *innerloopdata)
{
    _ufunc_masker_data *data;
    int iargs, nargs;
    PyUFuncGenericFunction unmasked_innerloop;
    void *unmasked_innerloopdata;
    npy_intp subloopsize;

    /* Put the aux data into local variables */
    data = (_ufunc_masker_data *)innerloopdata;
    unmasked_innerloop = data->unmasked_innerloop;
    unmasked_innerloopdata = data->unmasked_innerloopdata;
    nargs = data->nargs;

    /* Process the data as runs of unmasked values */
    do {
        /* Skip masked values */
        mask = npy_memchr(mask, 0, mask_stride, loopsize, &subloopsize, 1);
        for (iargs = 0; iargs < nargs; ++iargs) {
            dataptrs[iargs] += subloopsize * strides[iargs];
        }
        loopsize -= subloopsize;
        /*
         * Process unmasked values (assumes unmasked loop doesn't
         * mess with the 'args' pointer values)
         */
        mask = npy_memchr(mask, 0, mask_stride, loopsize, &subloopsize, 0);
        unmasked_innerloop(dataptrs, &subloopsize, strides,
                                        unmasked_innerloopdata);
        for (iargs = 0; iargs < nargs; ++iargs) {
            dataptrs[iargs] += subloopsize * strides[iargs];
        }
        loopsize -= subloopsize;
    } while (loopsize > 0);
}