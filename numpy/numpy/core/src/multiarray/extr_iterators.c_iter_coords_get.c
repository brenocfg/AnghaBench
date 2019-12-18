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
struct TYPE_3__ {int index; int* factors; int* coordinates; scalar_t__ contiguous; int /*<<< orphan*/  ao; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArrayIterObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyArray_IntTupleFromIntp (int,int*) ; 
 int PyArray_NDIM (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *
iter_coords_get(PyArrayIterObject *self)
{
    int nd;
    nd = PyArray_NDIM(self->ao);
    if (self->contiguous) {
        /*
         * coordinates not kept track of ---
         * need to generate from index
         */
        npy_intp val;
        int i;
        val = self->index;
        for (i = 0; i < nd; i++) {
            if (self->factors[i] != 0) {
                self->coordinates[i] = val / self->factors[i];
                val = val % self->factors[i];
            } else {
                self->coordinates[i] = 0;
            }
        }
    }
    return PyArray_IntTupleFromIntp(nd, self->coordinates);
}