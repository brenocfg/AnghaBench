#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t npy_intp ;
struct TYPE_13__ {char type; } ;
struct TYPE_12__ {size_t nin; size_t nout; int ntypes; } ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  NPY_CASTING ;

/* Variables and functions */
 int NPY_OBJECT ; 
 int NPY_VOID ; 
 int /*<<< orphan*/  PyArray_CanCastArrayTo (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_CanCastTypeTo (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 TYPE_2__* PyArray_DescrFromType (int) ; 
 int /*<<< orphan*/  PyObject_Print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_2__*) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
ufunc_loop_matches(PyUFuncObject *self,
                    PyArrayObject **op,
                    NPY_CASTING input_casting,
                    NPY_CASTING output_casting,
                    int any_object,
                    int use_min_scalar,
                    int *types, PyArray_Descr **dtypes,
                    int *out_no_castable_output,
                    char *out_err_src_typecode,
                    char *out_err_dst_typecode)
{
    npy_intp i, nin = self->nin, nop = nin + self->nout;

    /*
     * First check if all the inputs can be safely cast
     * to the types for this function
     */
    for (i = 0; i < nin; ++i) {
        PyArray_Descr *tmp;

        /*
         * If no inputs are objects and there are more than one
         * loop, don't allow conversion to object.  The rationale
         * behind this is mostly performance.  Except for custom
         * ufuncs built with just one object-parametered inner loop,
         * only the types that are supported are implemented.  Trying
         * the object version of logical_or on float arguments doesn't
         * seem right.
         */
        if (types[i] == NPY_OBJECT && !any_object && self->ntypes > 1) {
            return 0;
        }

        /*
         * If type num is NPY_VOID and struct dtypes have been passed in,
         * use struct dtype object. Otherwise create new dtype object
         * from type num.
         */
        if (types[i] == NPY_VOID && dtypes != NULL) {
            tmp = dtypes[i];
            Py_INCREF(tmp);
        }
        else {
            tmp = PyArray_DescrFromType(types[i]);
        }
        if (tmp == NULL) {
            return -1;
        }

#if NPY_UF_DBG_TRACING
        printf("Checking type for op %d, type %d: ", (int)i, (int)types[i]);
        PyObject_Print((PyObject *)tmp, stdout, 0);
        printf(", operand type: ");
        PyObject_Print((PyObject *)PyArray_DESCR(op[i]), stdout, 0);
        printf("\n");
#endif
        /*
         * If all the inputs are scalars, use the regular
         * promotion rules, not the special value-checking ones.
         */
        if (!use_min_scalar) {
            if (!PyArray_CanCastTypeTo(PyArray_DESCR(op[i]), tmp,
                                                    input_casting)) {
                Py_DECREF(tmp);
                return 0;
            }
        }
        else {
            if (!PyArray_CanCastArrayTo(op[i], tmp, input_casting)) {
                Py_DECREF(tmp);
                return 0;
            }
        }
        Py_DECREF(tmp);
    }

    /*
     * If all the inputs were ok, then check casting back to the
     * outputs.
     */
    for (i = nin; i < nop; ++i) {
        if (op[i] != NULL) {
            PyArray_Descr *tmp = PyArray_DescrFromType(types[i]);
            if (tmp == NULL) {
                return -1;
            }
            if (!PyArray_CanCastTypeTo(tmp, PyArray_DESCR(op[i]),
                                                        output_casting)) {
                if (!(*out_no_castable_output)) {
                    *out_no_castable_output = 1;
                    *out_err_src_typecode = tmp->type;
                    *out_err_dst_typecode = PyArray_DESCR(op[i])->type;
                }
                Py_DECREF(tmp);
                return 0;
            }
            Py_DECREF(tmp);
        }
    }

    return 1;
}