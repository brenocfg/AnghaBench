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
 int /*<<< orphan*/ * ObjectDir (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OutputAttrs ; 
 int /*<<< orphan*/  OutputMethods ; 
 int /*<<< orphan*/ * PyInt_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Py_FindMethod (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static PyObject *
OutputGetattr(PyObject *self, char *name)
{
    if (strcmp(name, "softspace") == 0)
	return PyInt_FromLong(((OutputObject *)(self))->softspace);
    else if (strcmp(name, "__members__") == 0)
	return ObjectDir(NULL, OutputAttrs);

    return Py_FindMethod(OutputMethods, self, name);
}