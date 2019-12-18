#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* v_list; TYPE_1__* v_dict; } ;
struct TYPE_17__ {int v_type; TYPE_3__ vval; } ;
typedef  TYPE_4__ typval_T ;
typedef  int (* pytotvfunc ) (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ;
struct TYPE_15__ {int /*<<< orphan*/  lv_refcount; } ;
struct TYPE_14__ {int /*<<< orphan*/  dv_refcount; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 TYPE_4__* PyCObject_AsVoidPtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyCObject_FromVoidPtr (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* PyCapsule_GetPointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyCapsule_New (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
#define  VAR_DICT 129 
#define  VAR_LIST 128 
 void* VAR_UNKNOWN ; 
 int /*<<< orphan*/  copy_tv (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
convert_dl(PyObject *obj, typval_T *tv,
				    pytotvfunc py_to_tv, PyObject *lookup_dict)
{
    PyObject	*capsule;
    char	hexBuf[sizeof(void *) * 2 + 3];

    sprintf(hexBuf, "%p", obj);

# ifdef PY_USE_CAPSULE
    capsule = PyDict_GetItemString(lookup_dict, hexBuf);
# else
    capsule = (PyObject *)PyDict_GetItemString(lookup_dict, hexBuf);
# endif
    if (capsule == NULL)
    {
# ifdef PY_USE_CAPSULE
	capsule = PyCapsule_New(tv, NULL, NULL);
# else
	capsule = PyCObject_FromVoidPtr(tv, NULL);
# endif
	if (PyDict_SetItemString(lookup_dict, hexBuf, capsule))
	{
	    Py_DECREF(capsule);
	    tv->v_type = VAR_UNKNOWN;
	    return -1;
	}

	Py_DECREF(capsule);

	if (py_to_tv(obj, tv, lookup_dict) == -1)
	{
	    tv->v_type = VAR_UNKNOWN;
	    return -1;
	}
	/* As we are not using copy_tv which increments reference count we must
	 * do it ourself. */
	switch(tv->v_type)
	{
	    case VAR_DICT: ++tv->vval.v_dict->dv_refcount; break;
	    case VAR_LIST: ++tv->vval.v_list->lv_refcount; break;
	}
    }
    else
    {
	typval_T	*v;

# ifdef PY_USE_CAPSULE
	v = PyCapsule_GetPointer(capsule, NULL);
# else
	v = PyCObject_AsVoidPtr(capsule);
# endif
	copy_tv(v, tv);
    }
    return 0;
}