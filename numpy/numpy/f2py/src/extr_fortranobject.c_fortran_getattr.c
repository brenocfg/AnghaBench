#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* d; } ;
struct TYPE_8__ {char* name; int rank; int /*<<< orphan*/ * data; int /*<<< orphan*/  type; TYPE_1__ dims; int /*<<< orphan*/  (* func ) (int*,int*,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_7__ {int len; int /*<<< orphan*/ * dict; TYPE_3__* defs; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PyFortranObject ;

/* Variables and functions */
 int /*<<< orphan*/ * F2PyCapsule_FromVoidPtr (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NPY_ARRAY_FARRAY ; 
 int /*<<< orphan*/ * PyArray_New (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GenericGetAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyString_ConcatAndDel (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyString_FromString (char*) ; 
 int /*<<< orphan*/ * PyUnicode_Concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyUnicode_FromString (char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_FindMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/ * fortran_doc (TYPE_3__) ; 
 int /*<<< orphan*/  fortran_methods ; 
 TYPE_3__* save_def ; 
 int /*<<< orphan*/  set_data ; 
 int strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int*,int*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static PyObject *
fortran_getattr(PyFortranObject *fp, char *name) {
    int i,j,k,flag;
    if (fp->dict != NULL) {
        PyObject *v = PyDict_GetItemString(fp->dict, name);
        if (v != NULL) {
            Py_INCREF(v);
            return v;
        }
    }
    for (i=0,j=1;i<fp->len && (j=strcmp(name,fp->defs[i].name));i++);
    if (j==0)
        if (fp->defs[i].rank!=-1) {                   /* F90 allocatable array */
            if (fp->defs[i].func==NULL) return NULL;
            for(k=0;k<fp->defs[i].rank;++k)
                fp->defs[i].dims.d[k]=-1;
            save_def = &fp->defs[i];
            (*(fp->defs[i].func))(&fp->defs[i].rank,fp->defs[i].dims.d,set_data,&flag);
            if (flag==2)
                k = fp->defs[i].rank + 1;
            else
                k = fp->defs[i].rank;
            if (fp->defs[i].data !=NULL) {              /* array is allocated */
                PyObject *v = PyArray_New(&PyArray_Type, k, fp->defs[i].dims.d,
                                          fp->defs[i].type, NULL, fp->defs[i].data, 0, NPY_ARRAY_FARRAY,
                                          NULL);
                if (v==NULL) return NULL;
                /* Py_INCREF(v); */
                return v;
            } else {                                    /* array is not allocated */
                Py_RETURN_NONE;
            }
        }
    if (strcmp(name,"__dict__")==0) {
        Py_INCREF(fp->dict);
        return fp->dict;
    }
    if (strcmp(name,"__doc__")==0) {
#if PY_VERSION_HEX >= 0x03000000
        PyObject *s = PyUnicode_FromString(""), *s2, *s3;
        for (i=0;i<fp->len;i++) {
            s2 = fortran_doc(fp->defs[i]);
            s3 = PyUnicode_Concat(s, s2);
            Py_DECREF(s2);
            Py_DECREF(s);
            s = s3;
        }
#else
        PyObject *s = PyString_FromString("");
        for (i=0;i<fp->len;i++)
            PyString_ConcatAndDel(&s,fortran_doc(fp->defs[i]));
#endif
        if (PyDict_SetItemString(fp->dict, name, s))
            return NULL;
        return s;
    }
    if ((strcmp(name,"_cpointer")==0) && (fp->len==1)) {
        PyObject *cobj = F2PyCapsule_FromVoidPtr((void *)(fp->defs[0].data),NULL);
        if (PyDict_SetItemString(fp->dict, name, cobj))
            return NULL;
        return cobj;
    }
#if PY_VERSION_HEX >= 0x03000000
    if (1) {
        PyObject *str, *ret;
        str = PyUnicode_FromString(name);
        ret = PyObject_GenericGetAttr((PyObject *)fp, str);
        Py_DECREF(str);
        return ret;
    }
#else
    return Py_FindMethod(fortran_methods, (PyObject *)fp, name);
#endif
}