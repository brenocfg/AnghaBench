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
struct sample_read_value {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyLong_FromUnsignedLongLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SetItem (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 

__attribute__((used)) static PyObject *get_sample_value_as_tuple(struct sample_read_value *value)
{
	PyObject *t;

	t = PyTuple_New(2);
	if (!t)
		Py_FatalError("couldn't create Python tuple");
	PyTuple_SetItem(t, 0, PyLong_FromUnsignedLongLong(value->id));
	PyTuple_SetItem(t, 1, PyLong_FromUnsignedLongLong(value->value));
	return t;
}