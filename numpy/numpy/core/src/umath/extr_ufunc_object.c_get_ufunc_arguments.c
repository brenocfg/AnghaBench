#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nin; int nout; int nargs; } ;
typedef  TYPE_1__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArray_Descr ;
typedef  int /*<<< orphan*/  PyArrayObject ;
typedef  int /*<<< orphan*/  NPY_ORDER ;
typedef  int /*<<< orphan*/  NPY_CASTING ;

/* Variables and functions */
 int /*<<< orphan*/  Generic ; 
 int /*<<< orphan*/  PyArray_CastingConverter ; 
 scalar_t__ PyArray_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DescrConverter2 ; 
 scalar_t__ PyArray_FromAny (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_FromArray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_IsScalar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_OrderConverter ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 scalar_t__ PyTuple_CheckExact (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 int PyTuple_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _borrowed_reference ; 
 int /*<<< orphan*/  _keepdims_converter ; 
 int /*<<< orphan*/  _new_reference ; 
 scalar_t__ _set_out_array (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _subok_converter ; 
 int /*<<< orphan*/  _wheremask_converter ; 
 int /*<<< orphan*/ * npy_um_str_axes ; 
 int /*<<< orphan*/ * npy_um_str_axis ; 
 int /*<<< orphan*/ * npy_um_str_casting ; 
 int /*<<< orphan*/ * npy_um_str_dtype ; 
 int /*<<< orphan*/ * npy_um_str_extobj ; 
 int /*<<< orphan*/ * npy_um_str_keepdims ; 
 int /*<<< orphan*/ * npy_um_str_order ; 
 int /*<<< orphan*/ * npy_um_str_out ; 
 int /*<<< orphan*/ * npy_um_str_sig ; 
 int /*<<< orphan*/ * npy_um_str_signature ; 
 int /*<<< orphan*/ * npy_um_str_subok ; 
 int /*<<< orphan*/ * npy_um_str_where ; 
 scalar_t__ parse_ufunc_keywords (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
get_ufunc_arguments(PyUFuncObject *ufunc,
                    PyObject *args, PyObject *kwds,
                    PyArrayObject **out_op,
                    NPY_ORDER *out_order,
                    NPY_CASTING *out_casting,
                    PyObject **out_extobj,
                    PyObject **out_typetup,  /* type: Tuple[np.dtype] */
                    int *out_subok,  /* bool */
                    PyArrayObject **out_wheremask, /* PyArray of bool */
                    PyObject **out_axes,  /* type: List[Tuple[T]] */
                    PyObject **out_axis,  /* type: T */
                    int *out_keepdims)  /* bool */
{
    int i, nargs;
    int nin = ufunc->nin;
    int nout = ufunc->nout;
    int nop = ufunc->nargs;
    PyObject *obj, *context;
    PyArray_Descr *dtype = NULL;
    /*
     * Initialize output objects so caller knows when outputs and optional
     * arguments are set (also means we can safely XDECREF on failure).
     */
    for (i = 0; i < nop; i++) {
        out_op[i] = NULL;
    }
    *out_extobj = NULL;
    *out_typetup = NULL;
    if (out_axes != NULL) {
        *out_axes = NULL;
    }
    if (out_axis != NULL) {
        *out_axis = NULL;
    }
    if (out_wheremask != NULL) {
        *out_wheremask = NULL;
    }

    /* Check number of arguments */
    nargs = PyTuple_Size(args);
    if ((nargs < nin) || (nargs > nop)) {
        PyErr_SetString(PyExc_ValueError, "invalid number of arguments");
        return -1;
    }

    /* Get input arguments */
    for (i = 0; i < nin; ++i) {
        obj = PyTuple_GET_ITEM(args, i);

        if (PyArray_Check(obj)) {
            PyArrayObject *obj_a = (PyArrayObject *)obj;
            out_op[i] = (PyArrayObject *)PyArray_FromArray(obj_a, NULL, 0);
        }
        else {
            if (!PyArray_IsScalar(obj, Generic)) {
                /*
                 * TODO: There should be a comment here explaining what
                 *       context does.
                 */
                context = Py_BuildValue("OOi", ufunc, args, i);
                if (context == NULL) {
                    goto fail;
                }
            }
            else {
                context = NULL;
            }
            out_op[i] = (PyArrayObject *)PyArray_FromAny(obj,
                                    NULL, 0, 0, 0, context);
            Py_XDECREF(context);
        }

        if (out_op[i] == NULL) {
            goto fail;
        }
    }

    /* Get positional output arguments */
    for (i = nin; i < nargs; ++i) {
        obj = PyTuple_GET_ITEM(args, i);
        if (_set_out_array(obj, out_op + i) < 0) {
            goto fail;
        }
    }

    /*
     * If keywords are present, get keyword output and other arguments.
     * Raise an error if anything else is present in the keyword dictionary.
     */
    if (kwds) {
        PyObject *out_kwd = NULL;
        PyObject *sig = NULL;
        static PyObject *kwnames[13] = {NULL};
        if (kwnames[0] == NULL) {
            kwnames[0] = npy_um_str_out;
            kwnames[1] = npy_um_str_where;
            kwnames[2] = npy_um_str_axes;
            kwnames[3] = npy_um_str_axis;
            kwnames[4] = npy_um_str_keepdims;
            kwnames[5] = npy_um_str_casting;
            kwnames[6] = npy_um_str_order;
            kwnames[7] = npy_um_str_dtype;
            kwnames[8] = npy_um_str_subok;
            kwnames[9] = npy_um_str_signature;
            kwnames[10] = npy_um_str_sig;
            kwnames[11] = npy_um_str_extobj;
            kwnames[12] = NULL;  /* sentinel */
        }
        /*
         * Parse using converters to calculate outputs
         * (NULL outputs are treated as indicating a keyword is not allowed).
         */
        if (parse_ufunc_keywords(
                ufunc, kwds, kwnames,
                _borrowed_reference, &out_kwd,
                _wheremask_converter, out_wheremask,  /* new reference */
                _new_reference, out_axes,
                _new_reference, out_axis,
                _keepdims_converter, out_keepdims,
                PyArray_CastingConverter, out_casting,
                PyArray_OrderConverter, out_order,
                PyArray_DescrConverter2, &dtype,   /* new reference */
                _subok_converter, out_subok,
                _new_reference, out_typetup,
                _borrowed_reference, &sig,
                _new_reference, out_extobj) < 0) {
            goto fail;
        }
        /*
         * Check that outputs were not passed as positional as well,
         * and that they are either None or an array.
         */
        if (out_kwd) {  /* borrowed reference */
            /*
             * Output arrays are generally specified as a tuple of arrays
             * and None, but may be a single array or None for ufuncs
             * with a single output.
             */
            if (nargs > nin) {
                PyErr_SetString(PyExc_ValueError,
                                "cannot specify 'out' as both a "
                                "positional and keyword argument");
                goto fail;
            }
            if (PyTuple_CheckExact(out_kwd)) {
                if (PyTuple_GET_SIZE(out_kwd) != nout) {
                    PyErr_SetString(PyExc_ValueError,
                                    "The 'out' tuple must have exactly "
                                    "one entry per ufunc output");
                    goto fail;
                }
                /* 'out' must be a tuple of arrays and Nones */
                for(i = 0; i < nout; ++i) {
                    PyObject *val = PyTuple_GET_ITEM(out_kwd, i);
                    if (_set_out_array(val, out_op+nin+i) < 0) {
                        goto fail;
                    }
                }
            }
            else if (nout == 1) {
                /* Can be an array if it only has one output */
                if (_set_out_array(out_kwd, out_op + nin) < 0) {
                    goto fail;
                }
            }
            else {
                PyErr_SetString(PyExc_TypeError,
                        nout > 1 ? "'out' must be a tuple of arrays" :
                                   "'out' must be an array or a tuple with "
                                   "a single array");
                goto fail;
            }
        }
        /*
         * Check we did not get both axis and axes, or multiple ways
         * to define a signature.
         */
        if (out_axes != NULL && out_axis != NULL &&
            *out_axes != NULL && *out_axis != NULL) {
            PyErr_SetString(PyExc_TypeError,
                            "cannot specify both 'axis' and 'axes'");
            goto fail;
        }
        if (sig) {  /* borrowed reference */
            if (*out_typetup != NULL) {
                PyErr_SetString(PyExc_ValueError,
                                "cannot specify both 'sig' and 'signature'");
                goto fail;
            }
            Py_INCREF(sig);
            *out_typetup = sig;
        }
        if (dtype) {  /* new reference */
            if (*out_typetup != NULL) {
                PyErr_SetString(PyExc_RuntimeError,
                                "cannot specify both 'signature' and 'dtype'");
                goto fail;
            }
            /* Note: "N" uses the reference */
            *out_typetup = Py_BuildValue("(N)", dtype);
        }
    }
    return 0;

fail:
    Py_XDECREF(dtype);
    Py_XDECREF(*out_typetup);
    Py_XDECREF(*out_extobj);
    if (out_wheremask != NULL) {
        Py_XDECREF(*out_wheremask);
    }
    if (out_axes != NULL) {
        Py_XDECREF(*out_axes);
    }
    if (out_axis != NULL) {
        Py_XDECREF(*out_axis);
    }
    for (i = 0; i < nop; i++) {
        Py_XDECREF(out_op[i]);
    }
    return -1;
}