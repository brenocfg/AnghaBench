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
typedef  int /*<<< orphan*/  PyObject ;
typedef  int NPY_CASTING ;

/* Variables and functions */
#define  NPY_EQUIV_CASTING 132 
#define  NPY_NO_CASTING 131 
#define  NPY_SAFE_CASTING 130 
#define  NPY_SAME_KIND_CASTING 129 
#define  NPY_UNSAFE_CASTING 128 
 int /*<<< orphan*/ * PyInt_FromLong (int) ; 
 int /*<<< orphan*/ * PyUString_FromString (char*) ; 

__attribute__((used)) static PyObject *
npy_casting_to_py_object(NPY_CASTING casting)
{
    switch (casting) {
        case NPY_NO_CASTING:
            return PyUString_FromString("no");
        case NPY_EQUIV_CASTING:
            return PyUString_FromString("equiv");
        case NPY_SAFE_CASTING:
            return PyUString_FromString("safe");
        case NPY_SAME_KIND_CASTING:
            return PyUString_FromString("same_kind");
        case NPY_UNSAFE_CASTING:
            return PyUString_FromString("unsafe");
        default:
            return PyInt_FromLong(casting);
    }
}