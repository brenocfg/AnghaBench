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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyTuple_New (unsigned int) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 

__attribute__((used)) static PyObject *tuple_new(unsigned int sz)
{
	PyObject *t;

	t = PyTuple_New(sz);
	if (!t)
		Py_FatalError("couldn't create Python tuple");
	return t;
}