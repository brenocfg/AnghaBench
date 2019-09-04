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
struct TYPE_8__ {int /*<<< orphan*/  (* copyswap ) (int /*<<< orphan*/ *,char*,int,TYPE_3__*) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ PyArrayObject ;

/* Variables and functions */
 scalar_t__ PyArray_ISBEHAVED_RO (TYPE_3__*) ; 
 int /*<<< orphan*/  PyArray_ISNOTSWAPPED (TYPE_3__*) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,char*,int,TYPE_3__*) ; 

__attribute__((used)) static PyObject *
twoint_getitem(char *ip, PyArrayObject *ap) {
    npy_int32 a[2];
 
    if ((ap==NULL) || PyArray_ISBEHAVED_RO(ap)) {
        a[0] = *((npy_int32 *)ip);
        a[1] = *((npy_int32 *)ip + 1);
    }
    else {
        ap->descr->f->copyswap(a, ip, !PyArray_ISNOTSWAPPED(ap), ap);
    }
    return Py_BuildValue("(ii)", a[0], a[1]);
}