#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_intp ;
struct TYPE_4__ {TYPE_1__* f; } ;
struct TYPE_3__ {int (* nonzero ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 scalar_t__ DEPRECATE (char*) ; 
 scalar_t__ Npy_EnterRecursiveCall (char*) ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 TYPE_2__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int PyArray_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_LeaveRecursiveCall () ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_array_nonzero(PyArrayObject *mp)
{
    npy_intp n;

    n = PyArray_SIZE(mp);
    if (n == 1) {
        int res;
        if (Npy_EnterRecursiveCall(" while converting array to bool")) {
            return -1;
        }
        res = PyArray_DESCR(mp)->f->nonzero(PyArray_DATA(mp), mp);
        /* nonzero has no way to indicate an error, but one can occur */
        if (PyErr_Occurred()) {
            res = -1;
        }
        Py_LeaveRecursiveCall();
        return res;
    }
    else if (n == 0) {
        /* 2017-09-25, 1.14 */
        if (DEPRECATE("The truth value of an empty array is ambiguous. "
                      "Returning False, but in future this will result in an error. "
                      "Use `array.size > 0` to check that an array is not empty.") < 0) {
            return -1;
        }
        return 0;
    }
    else {
        PyErr_SetString(PyExc_ValueError,
                        "The truth value of an array "
                        "with more than one element is ambiguous. "
                        "Use a.any() or a.all()");
        return -1;
    }
}