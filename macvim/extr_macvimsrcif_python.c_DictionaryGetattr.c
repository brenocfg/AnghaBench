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
 int /*<<< orphan*/  DictionaryAttrs ; 
 int /*<<< orphan*/  DictionaryMethods ; 
 int /*<<< orphan*/ * ObjectDir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyInt_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Py_FindMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static PyObject *
DictionaryGetattr(PyObject *self, char *name)
{
    DictionaryObject	*this = ((DictionaryObject *) (self));

    if (strcmp(name, "locked") == 0)
	return PyInt_FromLong(this->dict->dv_lock);
    else if (strcmp(name, "scope") == 0)
	return PyInt_FromLong(this->dict->dv_scope);
    else if (strcmp(name, "__members__") == 0)
	return ObjectDir(NULL, DictionaryAttrs);

    return Py_FindMethod(DictionaryMethods, self, name);
}