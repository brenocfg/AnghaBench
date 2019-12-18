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
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  NPY_CASTING ;

/* Variables and functions */
 int /*<<< orphan*/  NPY_IT_DBG_PRINT (char*) ; 
 int /*<<< orphan*/  NPY_IT_DBG_PRINT1 (char*,int) ; 
 int NPY_OP_ITFLAG_CAST ; 
 int NPY_OP_ITFLAG_READ ; 
 int NPY_OP_ITFLAG_WRITE ; 
 int /*<<< orphan*/  PyArray_CanCastArrayTo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_CanCastTypeTo (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_EquivTypes (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyObject_Print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyObject_Repr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUString_ConcatAndDel (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUString_FromFormat (char*,int,...) ; 
 int /*<<< orphan*/ * PyUString_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  npyiter_casting_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
npyiter_check_casting(int nop, PyArrayObject **op,
                    PyArray_Descr **op_dtype,
                    NPY_CASTING casting,
                    npyiter_opitflags *op_itflags)
{
    int iop;

    for(iop = 0; iop < nop; ++iop) {
        NPY_IT_DBG_PRINT1("Iterator: Checking casting for operand %d\n",
                            (int)iop);
#if NPY_IT_DBG_TRACING
        printf("op: ");
        if (op[iop] != NULL) {
            PyObject_Print((PyObject *)PyArray_DESCR(op[iop]), stdout, 0);
        }
        else {
            printf("<null>");
        }
        printf(", iter: ");
        PyObject_Print((PyObject *)op_dtype[iop], stdout, 0);
        printf("\n");
#endif
        /* If the types aren't equivalent, a cast is necessary */
        if (op[iop] != NULL && !PyArray_EquivTypes(PyArray_DESCR(op[iop]),
                                                     op_dtype[iop])) {
            /* Check read (op -> temp) casting */
            if ((op_itflags[iop] & NPY_OP_ITFLAG_READ) &&
                        !PyArray_CanCastArrayTo(op[iop],
                                          op_dtype[iop],
                                          casting)) {
                PyObject *errmsg;
                errmsg = PyUString_FromFormat(
                        "Iterator operand %d dtype could not be cast from ",
                        iop);
                PyUString_ConcatAndDel(&errmsg,
                        PyObject_Repr((PyObject *)PyArray_DESCR(op[iop])));
                PyUString_ConcatAndDel(&errmsg,
                        PyUString_FromString(" to "));
                PyUString_ConcatAndDel(&errmsg,
                        PyObject_Repr((PyObject *)op_dtype[iop]));
                PyUString_ConcatAndDel(&errmsg,
                        PyUString_FromFormat(" according to the rule %s",
                                npyiter_casting_to_string(casting)));
                PyErr_SetObject(PyExc_TypeError, errmsg);
                Py_DECREF(errmsg);
                return 0;
            }
            /* Check write (temp -> op) casting */
            if ((op_itflags[iop] & NPY_OP_ITFLAG_WRITE) &&
                        !PyArray_CanCastTypeTo(op_dtype[iop],
                                          PyArray_DESCR(op[iop]),
                                          casting)) {
                PyObject *errmsg;
                errmsg = PyUString_FromString(
                        "Iterator requested dtype could not be cast from ");
                PyUString_ConcatAndDel(&errmsg,
                        PyObject_Repr((PyObject *)op_dtype[iop]));
                PyUString_ConcatAndDel(&errmsg,
                        PyUString_FromString(" to "));
                PyUString_ConcatAndDel(&errmsg,
                        PyObject_Repr((PyObject *)PyArray_DESCR(op[iop])));
                PyUString_ConcatAndDel(&errmsg,
                        PyUString_FromFormat(", the operand %d dtype, "
                                "according to the rule %s",
                                iop,
                                npyiter_casting_to_string(casting)));
                PyErr_SetObject(PyExc_TypeError, errmsg);
                Py_DECREF(errmsg);
                return 0;
            }

            NPY_IT_DBG_PRINT("Iterator: Setting NPY_OP_ITFLAG_CAST "
                                "because the types aren't equivalent\n");
            /* Indicate that this operand needs casting */
            op_itflags[iop] |= NPY_OP_ITFLAG_CAST;
        }
    }

    return 1;
}