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
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 scalar_t__ cur_python_cb ; 
 int /*<<< orphan*/ * python_none () ; 
 int /*<<< orphan*/  remove_python_obs_callback (scalar_t__) ; 

__attribute__((used)) static PyObject *remove_current_callback(PyObject *self, PyObject *args)
{
	UNUSED_PARAMETER(self);
	UNUSED_PARAMETER(args);

	if (cur_python_cb)
		remove_python_obs_callback(cur_python_cb);
	return python_none();
}