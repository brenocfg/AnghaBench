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
struct TYPE_7__ {int elsize; TYPE_1__* subarray; } ;
struct TYPE_6__ {int /*<<< orphan*/  shape; TYPE_2__* base; } ;
typedef  TYPE_2__ PyArray_Descr ;

/* Variables and functions */
 int NPY_MAXDIMS ; 
 scalar_t__ PyInt_AsLong (int /*<<< orphan*/ ) ; 
 int PyTuple_Check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ ,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_2__*) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_2__*) ; 

__attribute__((used)) static int
_update_descr_and_dimensions(PyArray_Descr **des, npy_intp *newdims,
                             npy_intp *newstrides, int oldnd)
{
    PyArray_Descr *old;
    int newnd;
    int numnew;
    npy_intp *mydim;
    int i;
    int tuple;

    old = *des;
    *des = old->subarray->base;


    mydim = newdims + oldnd;
    tuple = PyTuple_Check(old->subarray->shape);
    if (tuple) {
        numnew = PyTuple_GET_SIZE(old->subarray->shape);
    }
    else {
        numnew = 1;
    }


    newnd = oldnd + numnew;
    if (newnd > NPY_MAXDIMS) {
        goto finish;
    }
    if (tuple) {
        for (i = 0; i < numnew; i++) {
            mydim[i] = (npy_intp) PyInt_AsLong(
                    PyTuple_GET_ITEM(old->subarray->shape, i));
        }
    }
    else {
        mydim[0] = (npy_intp) PyInt_AsLong(old->subarray->shape);
    }

    if (newstrides) {
        npy_intp tempsize;
        npy_intp *mystrides;

        mystrides = newstrides + oldnd;
        /* Make new strides -- always C-contiguous */
        tempsize = (*des)->elsize;
        for (i = numnew - 1; i >= 0; i--) {
            mystrides[i] = tempsize;
            tempsize *= mydim[i] ? mydim[i] : 1;
        }
    }

 finish:
    Py_INCREF(*des);
    Py_DECREF(old);
    return newnd;
}