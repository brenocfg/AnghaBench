#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  softspace; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ OutputObject ;

/* Variables and functions */
 int /*<<< orphan*/  GET_ATTR_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyObject_GenericGetAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  name ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static PyObject *
OutputGetattro(PyObject *self, PyObject *nameobj)
{
    GET_ATTR_STRING(name, nameobj);

    if (strcmp(name, "softspace") == 0)
	return PyLong_FromLong(((OutputObject *)(self))->softspace);

    return PyObject_GenericGetAttr(self, nameobj);
}