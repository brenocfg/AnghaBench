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

/* Variables and functions */
 int /*<<< orphan*/ * PyImport_AddModule (char*) ; 
 int /*<<< orphan*/ * PyModule_GetDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * main_dict ; 
 int /*<<< orphan*/ * main_module ; 
 int /*<<< orphan*/  try_call_object (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_start_sub(void)
{
	main_module = PyImport_AddModule("__main__");
	if (main_module == NULL)
		return -1;
	Py_INCREF(main_module);

	main_dict = PyModule_GetDict(main_module);
	if (main_dict == NULL)
		goto error;
	Py_INCREF(main_dict);

	try_call_object("trace_begin", NULL);

	return 0;

error:
	Py_XDECREF(main_dict);
	Py_XDECREF(main_module);
	return -1;
}