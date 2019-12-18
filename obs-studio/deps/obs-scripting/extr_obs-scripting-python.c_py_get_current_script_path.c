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
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyModule_GetDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PyObject *py_get_current_script_path(PyObject *self, PyObject *args)
{
	UNUSED_PARAMETER(args);
	return PyDict_GetItemString(PyModule_GetDict(self), "__script_dir__");
}