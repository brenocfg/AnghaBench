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
struct TYPE_3__ {int /*<<< orphan*/  softspace; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ OutputObject ;

/* Variables and functions */
 int /*<<< orphan*/  NUMBER_UNSIGNED ; 
 int /*<<< orphan*/  N_ (char*) ; 
 scalar_t__ NumberToLong (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyErr_FORMAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyErr_SET_STRING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_AttributeError ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
OutputSetattr(OutputObject *self, char *name, PyObject *valObject)
{
    if (valObject == NULL)
    {
	PyErr_SET_STRING(PyExc_AttributeError,
		N_("can't delete OutputObject attributes"));
	return -1;
    }

    if (strcmp(name, "softspace") == 0)
    {
	if (NumberToLong(valObject, &(self->softspace), NUMBER_UNSIGNED))
	    return -1;
	return 0;
    }

    PyErr_FORMAT(PyExc_AttributeError, N_("invalid attribute: %s"), name);
    return -1;
}