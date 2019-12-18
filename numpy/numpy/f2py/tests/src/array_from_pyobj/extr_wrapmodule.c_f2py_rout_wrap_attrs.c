#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  alignment; int /*<<< orphan*/  type; int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * PyArray_BASE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DATA (int /*<<< orphan*/ *) ; 
 TYPE_1__* PyArray_DESCR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_DIM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyArray_FLAGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_ITEMSIZE (int /*<<< orphan*/ *) ; 
 int PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_STRIDE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PyArray_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 int /*<<< orphan*/  PyInt_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SetItem (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *f2py_rout_wrap_attrs(PyObject *capi_self,
                                      PyObject *capi_args) {
  PyObject *arr_capi = Py_None;
  PyArrayObject *arr = NULL;
  PyObject *dimensions = NULL;
  PyObject *strides = NULL;
  char s[100];
  int i;
  memset(s,0,100*sizeof(char));
  if (!PyArg_ParseTuple(capi_args,"O!|:wrap.attrs",
                        &PyArray_Type,&arr_capi))
    return NULL;
  arr = (PyArrayObject *)arr_capi;
  sprintf(s,"%p",PyArray_DATA(arr));
  dimensions = PyTuple_New(PyArray_NDIM(arr));
  strides = PyTuple_New(PyArray_NDIM(arr));
  for (i=0;i<PyArray_NDIM(arr);++i) {
    PyTuple_SetItem(dimensions,i,PyInt_FromLong(PyArray_DIM(arr,i)));
    PyTuple_SetItem(strides,i,PyInt_FromLong(PyArray_STRIDE(arr,i)));
  }
  return Py_BuildValue("siNNO(cciii)ii",s,PyArray_NDIM(arr),
                       dimensions,strides,
                       (PyArray_BASE(arr)==NULL?Py_None:PyArray_BASE(arr)),
                       PyArray_DESCR(arr)->kind,
                       PyArray_DESCR(arr)->type,
                       PyArray_TYPE(arr),
                       PyArray_ITEMSIZE(arr),
                       PyArray_DESCR(arr)->alignment,
                       PyArray_FLAGS(arr),
                       PyArray_ITEMSIZE(arr));
}