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
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  v_dict; } ;
struct TYPE_17__ {TYPE_1__ vval; } ;
typedef  TYPE_2__ typval_T ;
struct TYPE_15__ {int /*<<< orphan*/  v_type; scalar_t__ v_lock; } ;
struct TYPE_18__ {int /*<<< orphan*/  di_key; TYPE_13__ di_tv; } ;
typedef  TYPE_3__ dictitem_T ;
struct TYPE_19__ {scalar_t__ dv_lock; } ;
typedef  TYPE_4__ dict_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_20__ {TYPE_4__* dict; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_5__ DictionaryObject ;

/* Variables and functions */
 int ConvertFromPyMapping (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int ConvertFromPyObject (int /*<<< orphan*/ *,TYPE_13__*) ; 
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyErr_FORMAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * PyIter_Next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_GetIter (int /*<<< orphan*/ *) ; 
 scalar_t__ PyObject_HasAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PySequence_Fast (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PySequence_Fast_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int PySequence_Fast_GET_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAISE_KEY_ADD_FAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAISE_LOCKED_DICTIONARY ; 
 int /*<<< orphan*/ * StringToChars (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  VAR_UNKNOWN ; 
 scalar_t__ VimTryEnd () ; 
 int /*<<< orphan*/  VimTryStart () ; 
 int /*<<< orphan*/  clear_tv (TYPE_2__*) ; 
 scalar_t__ dict_add (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dict_extend (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* dictitem_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictitem_free (TYPE_3__*) ; 

__attribute__((used)) static PyObject *
DictionaryUpdate(DictionaryObject *self, PyObject *args, PyObject *kwargs)
{
    dict_T	*dict = self->dict;

    if (dict->dv_lock)
    {
	RAISE_LOCKED_DICTIONARY;
	return NULL;
    }

    if (kwargs)
    {
	typval_T	tv;

	if (ConvertFromPyMapping(kwargs, &tv) == -1)
	    return NULL;

	VimTryStart();
	dict_extend(self->dict, tv.vval.v_dict, (char_u *) "force");
	clear_tv(&tv);
	if (VimTryEnd())
	    return NULL;
    }
    else
    {
	PyObject	*obj = NULL;

	if (!PyArg_ParseTuple(args, "|O", &obj))
	    return NULL;

	if (obj == NULL)
	{
	    Py_INCREF(Py_None);
	    return Py_None;
	}

	if (PyObject_HasAttrString(obj, "keys"))
	    return DictionaryUpdate(self, NULL, obj);
	else
	{
	    PyObject	*iterator;
	    PyObject	*item;

	    if (!(iterator = PyObject_GetIter(obj)))
		return NULL;

	    while ((item = PyIter_Next(iterator)))
	    {
		PyObject	*fast;
		PyObject	*keyObject;
		PyObject	*valObject;
		PyObject	*todecref;
		char_u		*key;
		dictitem_T	*di;

		if (!(fast = PySequence_Fast(item, "")))
		{
		    Py_DECREF(iterator);
		    Py_DECREF(item);
		    return NULL;
		}

		Py_DECREF(item);

		if (PySequence_Fast_GET_SIZE(fast) != 2)
		{
		    Py_DECREF(iterator);
		    Py_DECREF(fast);
		    PyErr_FORMAT(PyExc_ValueError,
			    N_("expected sequence element of size 2, "
			    "but got sequence of size %d"),
			    (int) PySequence_Fast_GET_SIZE(fast));
		    return NULL;
		}

		keyObject = PySequence_Fast_GET_ITEM(fast, 0);

		if (!(key = StringToChars(keyObject, &todecref)))
		{
		    Py_DECREF(iterator);
		    Py_DECREF(fast);
		    return NULL;
		}

		di = dictitem_alloc(key);

		Py_XDECREF(todecref);

		if (di == NULL)
		{
		    Py_DECREF(fast);
		    Py_DECREF(iterator);
		    PyErr_NoMemory();
		    return NULL;
		}
		di->di_tv.v_lock = 0;
		di->di_tv.v_type = VAR_UNKNOWN;

		valObject = PySequence_Fast_GET_ITEM(fast, 1);

		if (ConvertFromPyObject(valObject, &di->di_tv) == -1)
		{
		    Py_DECREF(iterator);
		    Py_DECREF(fast);
		    dictitem_free(di);
		    return NULL;
		}

		Py_DECREF(fast);

		if (dict_add(dict, di) == FAIL)
		{
		    RAISE_KEY_ADD_FAIL(di->di_key);
		    Py_DECREF(iterator);
		    dictitem_free(di);
		    return NULL;
		}
	    }

	    Py_DECREF(iterator);

	    /* Iterator may have finished due to an exception */
	    if (PyErr_Occurred())
		return NULL;
	}
    }
    Py_INCREF(Py_None);
    return Py_None;
}