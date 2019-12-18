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
typedef  int npyiter_opitflags ;
typedef  int npy_uint32 ;

/* Variables and functions */
 int NPY_ITER_ARRAYMASK ; 
 int NPY_ITER_COPY ; 
 int NPY_ITER_GLOBAL_FLAGS ; 
 int NPY_ITER_READONLY ; 
 int NPY_ITER_READWRITE ; 
 int NPY_ITER_UPDATEIFCOPY ; 
 int NPY_ITER_VIRTUAL ; 
 int NPY_ITER_WRITEMASKED ; 
 int NPY_ITER_WRITEONLY ; 
 int NPY_OP_ITFLAG_READ ; 
 int NPY_OP_ITFLAG_VIRTUAL ; 
 int NPY_OP_ITFLAG_WRITE ; 
 int NPY_OP_ITFLAG_WRITEMASKED ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 

__attribute__((used)) static int
npyiter_check_per_op_flags(npy_uint32 op_flags, npyiter_opitflags *op_itflags)
{
    if ((op_flags & NPY_ITER_GLOBAL_FLAGS) != 0) {
        PyErr_SetString(PyExc_ValueError,
                    "A global iterator flag was passed as a per-operand flag "
                    "to the iterator constructor");
        return 0;
    }

    /* Check the read/write flags */
    if (op_flags & NPY_ITER_READONLY) {
        /* The read/write flags are mutually exclusive */
        if (op_flags & (NPY_ITER_READWRITE|NPY_ITER_WRITEONLY)) {
            PyErr_SetString(PyExc_ValueError,
                    "Only one of the iterator flags READWRITE, "
                    "READONLY, and WRITEONLY may be "
                    "specified for an operand");
            return 0;
        }

        *op_itflags = NPY_OP_ITFLAG_READ;
    }
    else if (op_flags & NPY_ITER_READWRITE) {
        /* The read/write flags are mutually exclusive */
        if (op_flags & NPY_ITER_WRITEONLY) {
            PyErr_SetString(PyExc_ValueError,
                    "Only one of the iterator flags READWRITE, "
                    "READONLY, and WRITEONLY may be "
                    "specified for an operand");
            return 0;
        }

        *op_itflags = NPY_OP_ITFLAG_READ|NPY_OP_ITFLAG_WRITE;
    }
    else if(op_flags & NPY_ITER_WRITEONLY) {
        *op_itflags = NPY_OP_ITFLAG_WRITE;
    }
    else {
        PyErr_SetString(PyExc_ValueError,
                "None of the iterator flags READWRITE, "
                "READONLY, or WRITEONLY were "
                "specified for an operand");
        return 0;
    }

    /* Check the flags for temporary copies */
    if (((*op_itflags) & NPY_OP_ITFLAG_WRITE) &&
                (op_flags & (NPY_ITER_COPY |
                           NPY_ITER_UPDATEIFCOPY)) == NPY_ITER_COPY) {
        PyErr_SetString(PyExc_ValueError,
                "If an iterator operand is writeable, must use "
                "the flag UPDATEIFCOPY instead of "
                "COPY");
        return 0;
    }

    /* Check the flag for a write masked operands */
    if (op_flags & NPY_ITER_WRITEMASKED) {
        if (!((*op_itflags) & NPY_OP_ITFLAG_WRITE)) {
            PyErr_SetString(PyExc_ValueError,
                "The iterator flag WRITEMASKED may only "
                "be used with READWRITE or WRITEONLY");
            return 0;
        }
        if ((op_flags & NPY_ITER_ARRAYMASK) != 0) {
            PyErr_SetString(PyExc_ValueError,
                "The iterator flag WRITEMASKED may not "
                "be used together with ARRAYMASK");
            return 0;
        }
        *op_itflags |= NPY_OP_ITFLAG_WRITEMASKED;
    }

    if ((op_flags & NPY_ITER_VIRTUAL) != 0) {
        if ((op_flags & NPY_ITER_READWRITE) == 0) {
            PyErr_SetString(PyExc_ValueError,
                "The iterator flag VIRTUAL should be "
                "be used together with READWRITE");
            return 0;
        }
        *op_itflags |= NPY_OP_ITFLAG_VIRTUAL;
    }

    return 1;
}