#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  npy_int32 ;
struct TYPE_10__ {TYPE_2__* descr; } ;
struct TYPE_9__ {TYPE_1__* f; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* copyswap ) (char*,int /*<<< orphan*/ *,int,TYPE_3__*) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_ISBEHAVED (TYPE_3__*) ; 
 int /*<<< orphan*/  PyArray_ISNOTSWAPPED (TYPE_3__*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyTuple_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ *,int,TYPE_3__*) ; 

__attribute__((used)) static int
twoint_setitem(PyObject *op, char *ov, PyArrayObject *ap) {
    npy_int32 a[2];
    
    if (!PyTuple_Check(op)) {
        PyErr_SetString(PyExc_TypeError, "must be a tuple");
        return -1;
    }
    if (!PyArg_ParseTuple(op, "ii", a, a+1)) return -1;

    if (ap == NULL || PyArray_ISBEHAVED(ap)) {
        memcpy(ov, a, sizeof(double));
    }
    else {
        ap->descr->f->copyswap(ov, a, !PyArray_ISNOTSWAPPED(ap), ap);
    }
    return 0;
}