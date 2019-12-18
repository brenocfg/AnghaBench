#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_4__* v_dict; } ;
struct TYPE_16__ {TYPE_1__ vval; int /*<<< orphan*/  v_type; } ;
typedef  TYPE_2__ typval_T ;
struct TYPE_14__ {scalar_t__ v_lock; } ;
struct TYPE_17__ {TYPE_12__ di_tv; int /*<<< orphan*/  di_key; } ;
typedef  TYPE_3__ dictitem_T ;
struct TYPE_18__ {int /*<<< orphan*/  dv_refcount; } ;
typedef  TYPE_4__ dict_T ;
typedef  scalar_t__ char_u ;
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 scalar_t__ NUL ; 
 scalar_t__ PyDict_Next (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAISE_KEY_ADD_FAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAISE_NO_EMPTY_KEYS ; 
 scalar_t__* StringToChars (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  VAR_DICT ; 
 int _ConvertFromPyObject (int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_tv (TYPE_12__*) ; 
 scalar_t__ dict_add (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dict_unref (TYPE_4__*) ; 
 TYPE_3__* dictitem_alloc (scalar_t__*) ; 
 TYPE_4__* py_dict_alloc () ; 
 int /*<<< orphan*/  vim_free (TYPE_3__*) ; 

__attribute__((used)) static int
pydict_to_tv(PyObject *obj, typval_T *tv, PyObject *lookup_dict)
{
    dict_T	*dict;
    char_u	*key;
    dictitem_T	*di;
    PyObject	*keyObject;
    PyObject	*valObject;
    Py_ssize_t	iter = 0;

    if (!(dict = py_dict_alloc()))
	return -1;

    tv->v_type = VAR_DICT;
    tv->vval.v_dict = dict;

    while (PyDict_Next(obj, &iter, &keyObject, &valObject))
    {
	PyObject	*todecref = NULL;

	if (keyObject == NULL || valObject == NULL)
	{
	    dict_unref(dict);
	    return -1;
	}

	if (!(key = StringToChars(keyObject, &todecref)))
	{
	    dict_unref(dict);
	    return -1;
	}

	if (*key == NUL)
	{
	    dict_unref(dict);
	    Py_XDECREF(todecref);
	    RAISE_NO_EMPTY_KEYS;
	    return -1;
	}

	di = dictitem_alloc(key);

	Py_XDECREF(todecref);

	if (di == NULL)
	{
	    PyErr_NoMemory();
	    dict_unref(dict);
	    return -1;
	}
	di->di_tv.v_lock = 0;

	if (_ConvertFromPyObject(valObject, &di->di_tv, lookup_dict) == -1)
	{
	    vim_free(di);
	    dict_unref(dict);
	    return -1;
	}

	if (dict_add(dict, di) == FAIL)
	{
	    RAISE_KEY_ADD_FAIL(di->di_key);
	    clear_tv(&di->di_tv);
	    vim_free(di);
	    dict_unref(dict);
	    return -1;
	}
    }

    --dict->dv_refcount;
    return 0;
}