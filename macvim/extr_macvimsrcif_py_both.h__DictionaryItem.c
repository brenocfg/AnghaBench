#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hashitem_T ;
struct TYPE_7__ {int /*<<< orphan*/  di_tv; } ;
typedef  TYPE_1__ dictitem_T ;
struct TYPE_8__ {int /*<<< orphan*/  dv_hashtab; scalar_t__ dv_lock; } ;
typedef  TYPE_2__ dict_T ;
typedef  scalar_t__ char_u ;
struct TYPE_9__ {TYPE_2__* dict; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_3__ DictionaryObject ;

/* Variables and functions */
 int /*<<< orphan*/ * ConvertToPyObject (int /*<<< orphan*/ *) ; 
 int DICT_FLAG_HAS_DEFAULT ; 
 int DICT_FLAG_NONE_DEFAULT ; 
 int DICT_FLAG_POP ; 
 int DICT_FLAG_RETURN_BOOL ; 
 scalar_t__ HASHITEM_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ NUL ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_False ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/ * Py_True ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAISE_LOCKED_DICTIONARY ; 
 int /*<<< orphan*/  RAISE_NO_EMPTY_KEYS ; 
 scalar_t__* StringToChars (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_1__* dict_lookup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictitem_free (TYPE_1__*) ; 
 int /*<<< orphan*/ * hash_find (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  hash_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
_DictionaryItem(DictionaryObject *self, PyObject *args, int flags)
{
    PyObject	*keyObject;
    PyObject	*defObject = ((flags & DICT_FLAG_NONE_DEFAULT)? Py_None : NULL);
    PyObject	*ret;
    char_u	*key;
    dictitem_T	*di;
    dict_T	*dict = self->dict;
    hashitem_T	*hi;
    PyObject	*todecref;

    if (flags & DICT_FLAG_HAS_DEFAULT)
    {
	if (!PyArg_ParseTuple(args, "O|O", &keyObject, &defObject))
	    return NULL;
    }
    else
	keyObject = args;

    if (flags & DICT_FLAG_RETURN_BOOL)
	defObject = Py_False;

    if (!(key = StringToChars(keyObject, &todecref)))
	return NULL;

    if (*key == NUL)
    {
	RAISE_NO_EMPTY_KEYS;
	Py_XDECREF(todecref);
	return NULL;
    }

    hi = hash_find(&dict->dv_hashtab, key);

    Py_XDECREF(todecref);

    if (HASHITEM_EMPTY(hi))
    {
	if (defObject)
	{
	    Py_INCREF(defObject);
	    return defObject;
	}
	else
	{
	    PyErr_SetObject(PyExc_KeyError, keyObject);
	    return NULL;
	}
    }
    else if (flags & DICT_FLAG_RETURN_BOOL)
    {
	ret = Py_True;
	Py_INCREF(ret);
	return ret;
    }

    di = dict_lookup(hi);

    if (!(ret = ConvertToPyObject(&di->di_tv)))
	return NULL;

    if (flags & DICT_FLAG_POP)
    {
	if (dict->dv_lock)
	{
	    RAISE_LOCKED_DICTIONARY;
	    Py_DECREF(ret);
	    return NULL;
	}

	hash_remove(&dict->dv_hashtab, hi);
	dictitem_free(di);
    }

    return ret;
}