#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  v_type; scalar_t__ v_lock; } ;
typedef  TYPE_1__ typval_T ;
typedef  int /*<<< orphan*/  hashitem_T ;
struct TYPE_18__ {TYPE_1__ di_tv; int /*<<< orphan*/  di_key; } ;
typedef  TYPE_2__ dictitem_T ;
struct TYPE_19__ {int /*<<< orphan*/  dv_hashtab; scalar_t__ dv_lock; } ;
typedef  TYPE_3__ dict_T ;
typedef  scalar_t__ char_u ;
struct TYPE_20__ {TYPE_3__* dict; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  int PyInt ;
typedef  TYPE_4__ DictionaryObject ;

/* Variables and functions */
 int ConvertFromPyObject (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ FAIL ; 
 scalar_t__ NUL ; 
 int /*<<< orphan*/  PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAISE_KEY_ADD_FAIL (scalar_t__*) ; 
 int /*<<< orphan*/  RAISE_LOCKED_DICTIONARY ; 
 int /*<<< orphan*/  RAISE_NO_EMPTY_KEYS ; 
 scalar_t__* StringToChars (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  VAR_UNKNOWN ; 
 int /*<<< orphan*/  clear_tv (TYPE_1__*) ; 
 int /*<<< orphan*/  copy_tv (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ dict_add (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* dict_find (TYPE_3__*,scalar_t__*,int) ; 
 TYPE_2__* dictitem_alloc (scalar_t__*) ; 
 int /*<<< orphan*/  dictitem_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * hash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_free (TYPE_2__*) ; 

__attribute__((used)) static PyInt
DictionaryAssItem(
	DictionaryObject *self, PyObject *keyObject, PyObject *valObject)
{
    char_u	*key;
    typval_T	tv;
    dict_T	*dict = self->dict;
    dictitem_T	*di;
    PyObject	*todecref;

    if (dict->dv_lock)
    {
	RAISE_LOCKED_DICTIONARY;
	return -1;
    }

    if (!(key = StringToChars(keyObject, &todecref)))
	return -1;

    if (*key == NUL)
    {
	RAISE_NO_EMPTY_KEYS;
	Py_XDECREF(todecref);
	return -1;
    }

    di = dict_find(dict, key, -1);

    if (valObject == NULL)
    {
	hashitem_T	*hi;

	if (di == NULL)
	{
	    Py_XDECREF(todecref);
	    PyErr_SetObject(PyExc_KeyError, keyObject);
	    return -1;
	}
	hi = hash_find(&dict->dv_hashtab, di->di_key);
	hash_remove(&dict->dv_hashtab, hi);
	dictitem_free(di);
	Py_XDECREF(todecref);
	return 0;
    }

    if (ConvertFromPyObject(valObject, &tv) == -1)
    {
	Py_XDECREF(todecref);
	return -1;
    }

    if (di == NULL)
    {
	if (!(di = dictitem_alloc(key)))
	{
	    Py_XDECREF(todecref);
	    PyErr_NoMemory();
	    return -1;
	}
	di->di_tv.v_lock = 0;
	di->di_tv.v_type = VAR_UNKNOWN;

	if (dict_add(dict, di) == FAIL)
	{
	    vim_free(di);
	    dictitem_free(di);
	    RAISE_KEY_ADD_FAIL(key);
	    Py_XDECREF(todecref);
	    return -1;
	}
    }
    else
	clear_tv(&di->di_tv);

    Py_XDECREF(todecref);

    copy_tv(&tv, &di->di_tv);
    clear_tv(&tv);
    return 0;
}