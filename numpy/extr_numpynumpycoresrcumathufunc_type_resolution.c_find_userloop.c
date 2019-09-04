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
typedef  size_t npy_intp ;
struct TYPE_8__ {int type_num; } ;
struct TYPE_7__ {size_t nin; size_t nout; int /*<<< orphan*/  userloops; } ;
struct TYPE_6__ {int* arg_types; void* data; int /*<<< orphan*/  func; struct TYPE_6__* next; } ;
typedef  TYPE_1__ PyUFunc_Loop1d ;
typedef  TYPE_2__ PyUFuncObject ;
typedef  int /*<<< orphan*/  PyUFuncGenericFunction ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ PyArray_Descr ;

/* Variables and functions */
 int NPY_VOID ; 
 scalar_t__ NpyCapsule_AsVoidPtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_GetItem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyInt_FromLong (int) ; 
 scalar_t__ PyTypeNum_ISUSERDEF (int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
find_userloop(PyUFuncObject *ufunc,
                PyArray_Descr **dtypes,
                PyUFuncGenericFunction *out_innerloop,
                void **out_innerloopdata)
{
    npy_intp i, nin = ufunc->nin, j, nargs = nin + ufunc->nout;
    PyUFunc_Loop1d *funcdata;

    /* Use this to try to avoid repeating the same userdef loop search */
    int last_userdef = -1;

    for (i = 0; i < nargs; ++i) {
        int type_num;

        /* no more ufunc arguments to check */
        if (dtypes[i] == NULL) {
            break;
        }

        type_num = dtypes[i]->type_num;
        if (type_num != last_userdef &&
                (PyTypeNum_ISUSERDEF(type_num) || type_num == NPY_VOID)) {
            PyObject *key, *obj;

            last_userdef = type_num;

            key = PyInt_FromLong(type_num);
            if (key == NULL) {
                return -1;
            }
            obj = PyDict_GetItem(ufunc->userloops, key);
            Py_DECREF(key);
            if (obj == NULL) {
                continue;
            }
            for (funcdata = (PyUFunc_Loop1d *)NpyCapsule_AsVoidPtr(obj);
                 funcdata != NULL;
                 funcdata = funcdata->next) {
                int *types = funcdata->arg_types;

                for (j = 0; j < nargs; ++j) {
                    if (types[j] != dtypes[j]->type_num) {
                        break;
                    }
                }
                /* It matched */
                if (j == nargs) {
                    *out_innerloop = funcdata->func;
                    *out_innerloopdata = funcdata->data;
                    return 1;
                }
            }
        }
    }

    /* Didn't find a match */
    return 0;
}