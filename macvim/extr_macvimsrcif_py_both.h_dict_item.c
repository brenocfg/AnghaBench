#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  hashitem_T ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dict_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dict_val (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *
dict_item(hashitem_T *hi)
{
    PyObject	*keyObject;
    PyObject	*valObject;
    PyObject	*ret;

    if (!(keyObject = dict_key(hi)))
	return NULL;

    if (!(valObject = dict_val(hi)))
    {
	Py_DECREF(keyObject);
	return NULL;
    }

    ret = Py_BuildValue("(OO)", keyObject, valObject);

    Py_DECREF(keyObject);
    Py_DECREF(valObject);

    return ret;
}