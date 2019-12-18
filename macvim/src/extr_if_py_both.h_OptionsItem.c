#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ char_u ;
struct TYPE_3__ {int /*<<< orphan*/  from; int /*<<< orphan*/  opt_type; scalar_t__ (* Check ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ OptionsObject ;

/* Variables and functions */
 scalar_t__ NUL ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/ * PyBytes_FromString (char*) ; 
 int /*<<< orphan*/  PyErr_SET_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_SET_VIM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 int /*<<< orphan*/  PyExc_RuntimeError ; 
 int /*<<< orphan*/ * PyInt_FromLong (long) ; 
 int /*<<< orphan*/ * Py_False ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/ * Py_True ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAISE_NO_EMPTY_KEYS ; 
 int SOPT_BOOL ; 
 int SOPT_NUM ; 
 int SOPT_STRING ; 
 int SOPT_UNSET ; 
 scalar_t__* StringToChars (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int get_option_value_strict (scalar_t__*,long*,scalar_t__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vim_free (scalar_t__*) ; 

__attribute__((used)) static PyObject *
OptionsItem(OptionsObject *self, PyObject *keyObject)
{
    char_u	*key;
    int		flags;
    long	numval;
    char_u	*stringval;
    PyObject	*todecref;

    if (self->Check(self->from))
	return NULL;

    if (!(key = StringToChars(keyObject, &todecref)))
	return NULL;

    if (*key == NUL)
    {
	RAISE_NO_EMPTY_KEYS;
	Py_XDECREF(todecref);
	return NULL;
    }

    flags = get_option_value_strict(key, &numval, &stringval,
				    self->opt_type, self->from);

    Py_XDECREF(todecref);

    if (flags == 0)
    {
	PyErr_SetObject(PyExc_KeyError, keyObject);
	return NULL;
    }

    if (flags & SOPT_UNSET)
    {
	Py_INCREF(Py_None);
	return Py_None;
    }
    else if (flags & SOPT_BOOL)
    {
	PyObject	*ret;
	ret = numval ? Py_True : Py_False;
	Py_INCREF(ret);
	return ret;
    }
    else if (flags & SOPT_NUM)
	return PyInt_FromLong(numval);
    else if (flags & SOPT_STRING)
    {
	if (stringval)
	{
	    PyObject	*ret = PyBytes_FromString((char *)stringval);
	    vim_free(stringval);
	    return ret;
	}
	else
	{
	    PyErr_SET_STRING(PyExc_RuntimeError,
		    N_("unable to get option value"));
	    return NULL;
	}
    }
    else
    {
	PyErr_SET_VIM(N_("internal error: unknown option type"));
	return NULL;
    }
}