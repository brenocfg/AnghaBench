#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * (* fortranfunc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;
struct TYPE_5__ {TYPE_1__* defs; } ;
struct TYPE_4__ {int rank; int /*<<< orphan*/ * data; int /*<<< orphan*/ * func; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ PyFortranObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyErr_Format (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static PyObject*
fortran_call(PyFortranObject *fp, PyObject *arg, PyObject *kw) {
    int i = 0;
    /*  printf("fortran call
        name=%s,func=%p,data=%p,%p\n",fp->defs[i].name,
        fp->defs[i].func,fp->defs[i].data,&fp->defs[i].data); */
    if (fp->defs[i].rank==-1) {/* is Fortran routine */
        if (fp->defs[i].func==NULL) {
            PyErr_Format(PyExc_RuntimeError, "no function to call");
            return NULL;
        }
        else if (fp->defs[i].data==NULL)
            /* dummy routine */
            return (*((fortranfunc)(fp->defs[i].func)))((PyObject *)fp,arg,kw,NULL);
        else
            return (*((fortranfunc)(fp->defs[i].func)))((PyObject *)fp,arg,kw,
                                                        (void *)fp->defs[i].data);
    }
    PyErr_Format(PyExc_TypeError, "this fortran object is not callable");
    return NULL;
}