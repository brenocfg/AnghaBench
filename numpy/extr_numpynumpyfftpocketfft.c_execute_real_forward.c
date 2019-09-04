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
typedef  int /*<<< orphan*/ * rfft_plan ;
typedef  int npy_intp ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int NPY_ARRAY_DEFAULT ; 
 int NPY_ARRAY_ENSUREARRAY ; 
 int NPY_ARRAY_FORCECAST ; 
 int /*<<< orphan*/  NPY_CDOUBLE ; 
 int /*<<< orphan*/  NPY_DOUBLE ; 
 int /*<<< orphan*/  NPY_SIGINT_OFF ; 
 int /*<<< orphan*/  NPY_SIGINT_ON ; 
 scalar_t__ PyArray_DATA (int /*<<< orphan*/ *) ; 
 int PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 int* PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DescrFromType (int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_Empty (int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PyArray_FromAny (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int PyArray_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/  Py_BEGIN_ALLOW_THREADS ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_END_ALLOW_THREADS ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_rfft_plan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/ * make_rfft_plan (int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,double*,int) ; 
 scalar_t__ rfft_forward (int /*<<< orphan*/ *,double*,double) ; 

__attribute__((used)) static PyObject *
execute_real_forward(PyObject *a1, double fct)
{
    rfft_plan plan=NULL;
    int fail = 0;
    PyArrayObject *data = (PyArrayObject *)PyArray_FromAny(a1,
            PyArray_DescrFromType(NPY_DOUBLE), 1, 0,
            NPY_ARRAY_DEFAULT | NPY_ARRAY_ENSUREARRAY | NPY_ARRAY_FORCECAST,
            NULL);
    if (!data) return NULL;

    int ndim = PyArray_NDIM(data);
    const npy_intp *odim = PyArray_DIMS(data);
    int npts = odim[ndim - 1];
    npy_intp *tdim=(npy_intp *)malloc(ndim*sizeof(npy_intp));
    if (!tdim)
      { Py_XDECREF(data); return NULL; }
    for (int d=0; d<ndim-1; ++d)
      tdim[d] = odim[d];
    tdim[ndim-1] = npts/2 + 1;
    PyArrayObject *ret = (PyArrayObject *)PyArray_Empty(ndim,
            tdim, PyArray_DescrFromType(NPY_CDOUBLE), 0);
    free(tdim);
    if (!ret) fail=1;
    if (!fail) {
      int rstep = PyArray_DIM(ret, PyArray_NDIM(ret) - 1)*2;

      int nrepeats = PyArray_SIZE(data)/npts;
      double *rptr = (double *)PyArray_DATA(ret),
             *dptr = (double *)PyArray_DATA(data);

      Py_BEGIN_ALLOW_THREADS;
      NPY_SIGINT_ON;
      plan = make_rfft_plan(npts);
      if (!plan) fail=1;
      if (!fail)
        for (int i = 0; i < nrepeats; i++) {
            rptr[rstep-1] = 0.0;
            memcpy((char *)(rptr+1), dptr, npts*sizeof(double));
            if (rfft_forward(plan, rptr+1, fct)!=0) {fail=1; break;}
            rptr[0] = rptr[1];
            rptr[1] = 0.0;
            rptr += rstep;
            dptr += npts;
      }
      if (plan) destroy_rfft_plan(plan);
      NPY_SIGINT_OFF;
      Py_END_ALLOW_THREADS;
    }
    if (fail) {
      Py_XDECREF(data);
      Py_XDECREF(ret);
      return PyErr_NoMemory();
    }
    Py_DECREF(data);
    return (PyObject *)ret;
}