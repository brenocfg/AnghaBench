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
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int PyTuple_SetItem (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PyLong_FromLong (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tuple_set_s32(PyObject *t, unsigned int pos, s32 val)
{
	return PyTuple_SetItem(t, pos, _PyLong_FromLong(val));
}