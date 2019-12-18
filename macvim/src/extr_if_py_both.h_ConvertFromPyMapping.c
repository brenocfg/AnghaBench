#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* v_dict; } ;
struct TYPE_18__ {TYPE_2__ vval; int /*<<< orphan*/  v_type; } ;
typedef  TYPE_3__ typval_T ;
struct TYPE_20__ {TYPE_1__* dict; } ;
struct TYPE_19__ {int /*<<< orphan*/  ob_type; } ;
struct TYPE_16__ {int /*<<< orphan*/  dv_refcount; } ;
typedef  TYPE_4__ PyObject ;
typedef  TYPE_5__ DictionaryObject ;

/* Variables and functions */
 int /*<<< orphan*/  DictionaryType ; 
 int /*<<< orphan*/  N_ (char*) ; 
 scalar_t__ PyDict_Check (TYPE_4__*) ; 
 TYPE_4__* PyDict_New () ; 
 int /*<<< orphan*/  PyErr_FORMAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 scalar_t__ PyMapping_Check (TYPE_4__*) ; 
 scalar_t__ PyType_IsSubtype (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_4__*) ; 
 int /*<<< orphan*/  Py_TYPE_NAME (TYPE_4__*) ; 
 int /*<<< orphan*/  VAR_DICT ; 
 int convert_dl (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  pydict_to_tv ; 
 int /*<<< orphan*/  pymap_to_tv ; 

__attribute__((used)) static int
ConvertFromPyMapping(PyObject *obj, typval_T *tv)
{
    PyObject	*lookup_dict;
    int		ret;

    if (!(lookup_dict = PyDict_New()))
	return -1;

    if (PyType_IsSubtype(obj->ob_type, &DictionaryType))
    {
	tv->v_type = VAR_DICT;
	tv->vval.v_dict = (((DictionaryObject *)(obj))->dict);
	++tv->vval.v_dict->dv_refcount;
	ret = 0;
    }
    else if (PyDict_Check(obj))
	ret = convert_dl(obj, tv, pydict_to_tv, lookup_dict);
    else if (PyMapping_Check(obj))
	ret = convert_dl(obj, tv, pymap_to_tv, lookup_dict);
    else
    {
	PyErr_FORMAT(PyExc_TypeError,
		N_("unable to convert %s to vim dictionary"),
		Py_TYPE_NAME(obj));
	ret = -1;
    }
    Py_DECREF(lookup_dict);
    return ret;
}