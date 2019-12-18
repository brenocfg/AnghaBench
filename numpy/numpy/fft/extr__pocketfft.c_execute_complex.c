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
typedef  int /*<<< orphan*/ * cfft_plan ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int NPY_ARRAY_DEFAULT ; 
 int NPY_ARRAY_ENSUREARRAY ; 
 int NPY_ARRAY_ENSURECOPY ; 
 int NPY_ARRAY_FORCECAST ; 
 int /*<<< orphan*/  NPY_CDOUBLE ; 
 int /*<<< orphan*/  NPY_SIGINT_OFF ; 
 int /*<<< orphan*/  NPY_SIGINT_ON ; 
 scalar_t__ PyArray_DATA (int /*<<< orphan*/ *) ; 
 int PyArray_DIM (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  PyArray_DescrFromType (int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_FromAny (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int PyArray_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/  Py_BEGIN_ALLOW_THREADS ; 
 int /*<<< orphan*/  Py_END_ALLOW_THREADS ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int cfft_backward (int /*<<< orphan*/ *,double*,double) ; 
 int cfft_forward (int /*<<< orphan*/ *,double*,double) ; 
 int /*<<< orphan*/  destroy_cfft_plan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_cfft_plan (int) ; 

__attribute__((used)) static PyObject *
execute_complex(PyObject *a1, int is_forward, double fct)
{
    PyArrayObject *data = (PyArrayObject *)PyArray_FromAny(a1,
            PyArray_DescrFromType(NPY_CDOUBLE), 1, 0,
            NPY_ARRAY_ENSURECOPY | NPY_ARRAY_DEFAULT |
            NPY_ARRAY_ENSUREARRAY | NPY_ARRAY_FORCECAST,
            NULL);
    if (!data) return NULL;

    int npts = PyArray_DIM(data, PyArray_NDIM(data) - 1);
    cfft_plan plan=NULL;

    int nrepeats = PyArray_SIZE(data)/npts;
    double *dptr = (double *)PyArray_DATA(data);
    int fail=0;
    Py_BEGIN_ALLOW_THREADS;
    NPY_SIGINT_ON;
    plan = make_cfft_plan(npts);
    if (!plan) fail=1;
    if (!fail)
      for (int i = 0; i < nrepeats; i++) {
          int res = is_forward ?
            cfft_forward(plan, dptr, fct) : cfft_backward(plan, dptr, fct);
          if (res!=0) { fail=1; break; }
          dptr += npts*2;
      }
    if (plan) destroy_cfft_plan(plan);
    NPY_SIGINT_OFF;
    Py_END_ALLOW_THREADS;
    if (fail) {
      Py_XDECREF(data);
      return PyErr_NoMemory();
    }
    return (PyObject *)data;
}