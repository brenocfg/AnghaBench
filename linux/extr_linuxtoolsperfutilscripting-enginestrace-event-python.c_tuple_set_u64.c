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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */

__attribute__((used)) static int tuple_set_u64(PyObject *t, unsigned int pos, u64 val)
{
#if BITS_PER_LONG == 64
	return PyTuple_SetItem(t, pos, _PyLong_FromLong(val));
#endif
#if BITS_PER_LONG == 32
	return PyTuple_SetItem(t, pos, PyLong_FromLongLong(val));
#endif
}