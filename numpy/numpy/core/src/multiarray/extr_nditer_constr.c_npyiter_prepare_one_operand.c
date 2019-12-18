#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int npyiter_opitflags ;
typedef  int npy_uint32 ;
struct TYPE_14__ {int flags; int /*<<< orphan*/  byteorder; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  IsAligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NPY_BOOL ; 
 int NPY_ITEM_IS_POINTER ; 
 int NPY_ITEM_REFCOUNT ; 
 int NPY_ITER_ALIGNED ; 
 int NPY_ITER_ALLOCATE ; 
 int NPY_ITER_ARRAYMASK ; 
 int NPY_ITER_BUFFERED ; 
 int NPY_ITER_DELAY_BUFALLOC ; 
 int NPY_ITER_NBO ; 
 int NPY_ITER_REFS_OK ; 
 int NPY_ITER_VIRTUAL ; 
 int NPY_ITER_ZEROSIZE_OK ; 
 int /*<<< orphan*/  NPY_IT_DBG_PRINT (char*) ; 
 int /*<<< orphan*/  NPY_NATIVE ; 
 int NPY_OP_ITFLAG_CAST ; 
 int NPY_OP_ITFLAG_READ ; 
 int NPY_OP_ITFLAG_WRITE ; 
 TYPE_1__* PyArray_AdaptFlexibleDType (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 char* PyArray_BYTES (int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_Check (int /*<<< orphan*/ *) ; 
 TYPE_1__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 TYPE_1__* PyArray_DescrFromType (int /*<<< orphan*/ ) ; 
 TYPE_1__* PyArray_DescrNewByteorder (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_FailUnlessWriteable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyArray_ISNBO (int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_XINCREF (TYPE_1__*) ; 

__attribute__((used)) static int
npyiter_prepare_one_operand(PyArrayObject **op,
                        char **op_dataptr,
                        PyArray_Descr *op_request_dtype,
                        PyArray_Descr **op_dtype,
                        npy_uint32 flags,
                        npy_uint32 op_flags, npyiter_opitflags *op_itflags)
{
    /* NULL operands must be automatically allocated outputs */
    if (*op == NULL) {
        /* ALLOCATE or VIRTUAL should be enabled */
        if ((op_flags & (NPY_ITER_ALLOCATE|NPY_ITER_VIRTUAL)) == 0) {
            PyErr_SetString(PyExc_ValueError,
                    "Iterator operand was NULL, but neither the "
                    "ALLOCATE nor the VIRTUAL flag was specified");
            return 0;
        }

        if (op_flags & NPY_ITER_ALLOCATE) {
            /* Writing should be enabled */
            if (!((*op_itflags) & NPY_OP_ITFLAG_WRITE)) {
                PyErr_SetString(PyExc_ValueError,
                        "Automatic allocation was requested for an iterator "
                        "operand, but it wasn't flagged for writing");
                return 0;
            }
            /*
             * Reading should be disabled if buffering is enabled without
             * also enabling NPY_ITER_DELAY_BUFALLOC.  In all other cases,
             * the caller may initialize the allocated operand to a value
             * before beginning iteration.
             */
            if (((flags & (NPY_ITER_BUFFERED |
                            NPY_ITER_DELAY_BUFALLOC)) == NPY_ITER_BUFFERED) &&
                    ((*op_itflags) & NPY_OP_ITFLAG_READ)) {
                PyErr_SetString(PyExc_ValueError,
                        "Automatic allocation was requested for an iterator "
                        "operand, and it was flagged as readable, but "
                        "buffering  without delayed allocation was enabled");
                return 0;
            }

            /* If a requested dtype was provided, use it, otherwise NULL */
            Py_XINCREF(op_request_dtype);
            *op_dtype = op_request_dtype;
        }
        else {
            *op_dtype = NULL;
        }

        /* Specify bool if no dtype was requested for the mask */
        if (op_flags & NPY_ITER_ARRAYMASK) {
            if (*op_dtype == NULL) {
                *op_dtype = PyArray_DescrFromType(NPY_BOOL);
                if (*op_dtype == NULL) {
                    return 0;
                }
            }
        }

        *op_dataptr = NULL;

        return 1;
    }

    /* VIRTUAL operands must be NULL */
    if (op_flags & NPY_ITER_VIRTUAL) {
        PyErr_SetString(PyExc_ValueError,
                "Iterator operand flag VIRTUAL was specified, "
                "but the operand was not NULL");
        return 0;
    }


    if (PyArray_Check(*op)) {

        if ((*op_itflags) & NPY_OP_ITFLAG_WRITE
            && PyArray_FailUnlessWriteable(*op, "operand array with iterator "
                                           "write flag set") < 0) {
            return 0;
        }
        if (!(flags & NPY_ITER_ZEROSIZE_OK) && PyArray_SIZE(*op) == 0) {
            PyErr_SetString(PyExc_ValueError,
                    "Iteration of zero-sized operands is not enabled");
            return 0;
        }
        *op_dataptr = PyArray_BYTES(*op);
        /* PyArray_DESCR does not give us a reference */
        *op_dtype = PyArray_DESCR(*op);
        if (*op_dtype == NULL) {
            PyErr_SetString(PyExc_ValueError,
                    "Iterator input operand has no dtype descr");
            return 0;
        }
        Py_INCREF(*op_dtype);
        /*
         * If references weren't specifically allowed, make sure there
         * are no references in the inputs or requested dtypes.
         */
        if (!(flags & NPY_ITER_REFS_OK)) {
            PyArray_Descr *dt = PyArray_DESCR(*op);
            if (((dt->flags & (NPY_ITEM_REFCOUNT |
                           NPY_ITEM_IS_POINTER)) != 0) ||
                    (dt != *op_dtype &&
                        (((*op_dtype)->flags & (NPY_ITEM_REFCOUNT |
                                             NPY_ITEM_IS_POINTER))) != 0)) {
                PyErr_SetString(PyExc_TypeError,
                        "Iterator operand or requested dtype holds "
                        "references, but the REFS_OK flag was not enabled");
                return 0;
            }
        }
        /*
         * Checking whether casts are valid is done later, once the
         * final data types have been selected.  For now, just store the
         * requested type.
         */
        if (op_request_dtype != NULL) {
            /* We just have a borrowed reference to op_request_dtype */
            Py_INCREF(op_request_dtype);
            /* If the requested dtype is flexible, adapt it */
            op_request_dtype = PyArray_AdaptFlexibleDType((PyObject *)(*op), PyArray_DESCR(*op),
                                                          op_request_dtype);
            if (op_request_dtype == NULL) {
                return 0;
            }

            /* Store the requested dtype */
            Py_DECREF(*op_dtype);
            *op_dtype = op_request_dtype;
        }

        /* Check if the operand is in the byte order requested */
        if (op_flags & NPY_ITER_NBO) {
            /* Check byte order */
            if (!PyArray_ISNBO((*op_dtype)->byteorder)) {
                PyArray_Descr *nbo_dtype;

                /* Replace with a new descr which is in native byte order */
                nbo_dtype = PyArray_DescrNewByteorder(*op_dtype, NPY_NATIVE);
                Py_DECREF(*op_dtype);
                *op_dtype = nbo_dtype;

                NPY_IT_DBG_PRINT("Iterator: Setting NPY_OP_ITFLAG_CAST "
                                    "because of NPY_ITER_NBO\n");
                /* Indicate that byte order or alignment needs fixing */
                *op_itflags |= NPY_OP_ITFLAG_CAST;
            }
        }
        /* Check if the operand is aligned */
        if (op_flags & NPY_ITER_ALIGNED) {
            /* Check alignment */
            if (!IsAligned(*op)) {
                NPY_IT_DBG_PRINT("Iterator: Setting NPY_OP_ITFLAG_CAST "
                                    "because of NPY_ITER_ALIGNED\n");
                *op_itflags |= NPY_OP_ITFLAG_CAST;
            }
        }
        /*
         * The check for NPY_ITER_CONTIG can only be done later,
         * once the final iteration order is settled.
         */
    }
    else {
        PyErr_SetString(PyExc_ValueError,
                "Iterator inputs must be ndarrays");
        return 0;
    }

    return 1;
}