#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dict; } ;
struct TYPE_3__ {int /*<<< orphan*/  dv_scope; int /*<<< orphan*/  dv_lock; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ DictionaryObject ;

/* Variables and functions */
 int /*<<< orphan*/  GET_ATTR_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyObject_GenericGetAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static PyObject *
DictionaryGetattro(PyObject *self, PyObject *nameobj)
{
    DictionaryObject	*this = ((DictionaryObject *) (self));

    GET_ATTR_STRING(name, nameobj);

    if (strcmp(name, "locked") == 0)
	return PyLong_FromLong(this->dict->dv_lock);
    else if (strcmp(name, "scope") == 0)
	return PyLong_FromLong(this->dict->dv_scope);

    return PyObject_GenericGetAttr(self, nameobj);
}