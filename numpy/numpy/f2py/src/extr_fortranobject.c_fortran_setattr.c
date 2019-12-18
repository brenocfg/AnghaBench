#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int npy_intp ;
struct TYPE_5__ {int* d; } ;
struct TYPE_7__ {int rank; int* data; int /*<<< orphan*/  (* func ) (int*,int*,int /*<<< orphan*/ ,int*) ;TYPE_1__ dims; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int len; int /*<<< orphan*/ * dict; TYPE_3__* defs; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PyFortranObject ;
typedef  int /*<<< orphan*/  PyArrayObject ;

/* Variables and functions */
 int /*<<< orphan*/  F2PY_INTENT_IN ; 
 int F2PY_MAX_DIMS ; 
 int* PyArray_DATA (int /*<<< orphan*/ *) ; 
 int* PyArray_DIMS (int /*<<< orphan*/ *) ; 
 int PyArray_ITEMSIZE (int /*<<< orphan*/ *) ; 
 int PyArray_MultiplyList (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyArray_NDIM (int /*<<< orphan*/ *) ; 
 int PyDict_DelItemString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 int PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_AttributeError ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/ * array_from_pyobj (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * memcpy (int*,int*,int) ; 
 TYPE_3__* save_def ; 
 int /*<<< orphan*/  set_data ; 
 int strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (int*,int*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
fortran_setattr(PyFortranObject *fp, char *name, PyObject *v) {
    int i,j,flag;
    PyArrayObject *arr = NULL;
    for (i=0,j=1;i<fp->len && (j=strcmp(name,fp->defs[i].name));i++);
    if (j==0) {
        if (fp->defs[i].rank==-1) {
            PyErr_SetString(PyExc_AttributeError,"over-writing fortran routine");
            return -1;
        }
        if (fp->defs[i].func!=NULL) { /* is allocatable array */
            npy_intp dims[F2PY_MAX_DIMS];
            int k;
            save_def = &fp->defs[i];
            if (v!=Py_None) {     /* set new value (reallocate if needed --
                                     see f2py generated code for more
                                     details ) */
                for(k=0;k<fp->defs[i].rank;k++) dims[k]=-1;
                if ((arr = array_from_pyobj(fp->defs[i].type,dims,fp->defs[i].rank,F2PY_INTENT_IN,v))==NULL)
                    return -1;
                (*(fp->defs[i].func))(&fp->defs[i].rank,PyArray_DIMS(arr),set_data,&flag);
            } else {             /* deallocate */
                for(k=0;k<fp->defs[i].rank;k++) dims[k]=0;
                (*(fp->defs[i].func))(&fp->defs[i].rank,dims,set_data,&flag);
                for(k=0;k<fp->defs[i].rank;k++) dims[k]=-1;
            }
            memcpy(fp->defs[i].dims.d,dims,fp->defs[i].rank*sizeof(npy_intp));
        } else {                     /* not allocatable array */
            if ((arr = array_from_pyobj(fp->defs[i].type,fp->defs[i].dims.d,fp->defs[i].rank,F2PY_INTENT_IN,v))==NULL)
                return -1;
        }
        if (fp->defs[i].data!=NULL) { /* copy Python object to Fortran array */
            npy_intp s = PyArray_MultiplyList(fp->defs[i].dims.d,PyArray_NDIM(arr));
            if (s==-1)
                s = PyArray_MultiplyList(PyArray_DIMS(arr),PyArray_NDIM(arr));
            if (s<0 ||
                (memcpy(fp->defs[i].data,PyArray_DATA(arr),s*PyArray_ITEMSIZE(arr)))==NULL) {
                if ((PyObject*)arr!=v) {
                    Py_DECREF(arr);
                }
                return -1;
            }
            if ((PyObject*)arr!=v) {
                Py_DECREF(arr);
            }
        } else return (fp->defs[i].func==NULL?-1:0);
        return 0; /* successful */
    }
    if (fp->dict == NULL) {
        fp->dict = PyDict_New();
        if (fp->dict == NULL)
            return -1;
    }
    if (v == NULL) {
        int rv = PyDict_DelItemString(fp->dict, name);
        if (rv < 0)
            PyErr_SetString(PyExc_AttributeError,"delete non-existing fortran attribute");
        return rv;
    }
    else
        return PyDict_SetItemString(fp->dict, name, v);
}