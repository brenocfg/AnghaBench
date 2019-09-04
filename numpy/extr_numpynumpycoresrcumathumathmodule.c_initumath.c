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

/* Variables and functions */
 scalar_t__ NPY_BUFSIZE ; 
 int /*<<< orphan*/  NPY_E ; 
 int /*<<< orphan*/  NPY_EULER ; 
 int /*<<< orphan*/  NPY_INFINITY ; 
 int /*<<< orphan*/  NPY_NAN ; 
 int /*<<< orphan*/  NPY_NZERO ; 
 int /*<<< orphan*/  NPY_PI ; 
 int /*<<< orphan*/  NPY_PZERO ; 
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/ * PyFloat_FromDouble (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyModule_AddIntConstant (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  PyModule_AddObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyModule_AddStringConstant (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyModule_GetDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 long UFUNC_ERR_CALL ; 
 long UFUNC_ERR_DEFAULT ; 
 long UFUNC_ERR_IGNORE ; 
 long UFUNC_ERR_LOG ; 
 long UFUNC_ERR_PRINT ; 
 long UFUNC_ERR_RAISE ; 
 long UFUNC_ERR_WARN ; 
 long UFUNC_FPE_DIVIDEBYZERO ; 
 long UFUNC_FPE_INVALID ; 
 long UFUNC_FPE_OVERFLOW ; 
 long UFUNC_FPE_UNDERFLOW ; 
 int /*<<< orphan*/  UFUNC_PYVALS_NAME ; 
 long UFUNC_SHIFT_DIVIDEBYZERO ; 
 long UFUNC_SHIFT_INVALID ; 
 long UFUNC_SHIFT_OVERFLOW ; 
 long UFUNC_SHIFT_UNDERFLOW ; 
 int /*<<< orphan*/  _PyArray_SetNumericOps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intern_strings () ; 

int initumath(PyObject *m)
{
    PyObject *d, *s, *s2;
    int UFUNC_FLOATING_POINT_SUPPORT = 1;

#ifdef NO_UFUNC_FLOATING_POINT_SUPPORT
    UFUNC_FLOATING_POINT_SUPPORT = 0;
#endif

    /* Add some symbolic constants to the module */
    d = PyModule_GetDict(m);

    PyDict_SetItemString(d, "pi", s = PyFloat_FromDouble(NPY_PI));
    Py_DECREF(s);
    PyDict_SetItemString(d, "e", s = PyFloat_FromDouble(NPY_E));
    Py_DECREF(s);
    PyDict_SetItemString(d, "euler_gamma", s = PyFloat_FromDouble(NPY_EULER));
    Py_DECREF(s);

#define ADDCONST(str) PyModule_AddIntConstant(m, #str, UFUNC_##str)
#define ADDSCONST(str) PyModule_AddStringConstant(m, "UFUNC_" #str, UFUNC_##str)

    ADDCONST(ERR_IGNORE);
    ADDCONST(ERR_WARN);
    ADDCONST(ERR_CALL);
    ADDCONST(ERR_RAISE);
    ADDCONST(ERR_PRINT);
    ADDCONST(ERR_LOG);
    ADDCONST(ERR_DEFAULT);

    ADDCONST(SHIFT_DIVIDEBYZERO);
    ADDCONST(SHIFT_OVERFLOW);
    ADDCONST(SHIFT_UNDERFLOW);
    ADDCONST(SHIFT_INVALID);

    ADDCONST(FPE_DIVIDEBYZERO);
    ADDCONST(FPE_OVERFLOW);
    ADDCONST(FPE_UNDERFLOW);
    ADDCONST(FPE_INVALID);

    ADDCONST(FLOATING_POINT_SUPPORT);

    ADDSCONST(PYVALS_NAME);

#undef ADDCONST
#undef ADDSCONST
    PyModule_AddIntConstant(m, "UFUNC_BUFSIZE_DEFAULT", (long)NPY_BUFSIZE);

    PyModule_AddObject(m, "PINF", PyFloat_FromDouble(NPY_INFINITY));
    PyModule_AddObject(m, "NINF", PyFloat_FromDouble(-NPY_INFINITY));
    PyModule_AddObject(m, "PZERO", PyFloat_FromDouble(NPY_PZERO));
    PyModule_AddObject(m, "NZERO", PyFloat_FromDouble(NPY_NZERO));
    PyModule_AddObject(m, "NAN", PyFloat_FromDouble(NPY_NAN));

#if defined(NPY_PY3K)
    s = PyDict_GetItemString(d, "true_divide");
    PyDict_SetItemString(d, "divide", s);
#endif

    s = PyDict_GetItemString(d, "conjugate");
    s2 = PyDict_GetItemString(d, "remainder");
    /* Setup the array object's numerical structures with appropriate
       ufuncs in d*/
    _PyArray_SetNumericOps(d);

    PyDict_SetItemString(d, "conj", s);
    PyDict_SetItemString(d, "mod", s2);

    if (!intern_strings()) {
        PyErr_SetString(PyExc_RuntimeError,
           "cannot intern umath strings while initializing _multiarray_umath.");
        return -1;
    }

    return 0;
}