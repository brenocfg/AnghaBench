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
 int /*<<< orphan*/  PyCallable_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  main_dict ; 

__attribute__((used)) static PyObject *get_handler(const char *handler_name)
{
	PyObject *handler;

	handler = PyDict_GetItemString(main_dict, handler_name);
	if (handler && !PyCallable_Check(handler))
		return NULL;
	return handler;
}