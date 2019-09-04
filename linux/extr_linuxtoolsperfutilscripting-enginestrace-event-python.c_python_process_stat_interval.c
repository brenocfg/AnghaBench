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
 int /*<<< orphan*/  MAX_FIELDS ; 
 int /*<<< orphan*/ * PyTuple_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int _PyTuple_Resize (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  call_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * get_handler (char const*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  tuple_set_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void python_process_stat_interval(u64 tstamp)
{
	PyObject *handler, *t;
	static const char handler_name[] = "stat__interval";
	int n = 0;

	t = PyTuple_New(MAX_FIELDS);
	if (!t)
		Py_FatalError("couldn't create Python tuple");

	handler = get_handler(handler_name);
	if (!handler) {
		pr_debug("can't find python handler %s\n", handler_name);
		return;
	}

	tuple_set_u64(t, n++, tstamp);

	if (_PyTuple_Resize(&t, n) == -1)
		Py_FatalError("error resizing Python tuple");

	call_object(handler, t, handler_name);

	Py_DECREF(t);
}