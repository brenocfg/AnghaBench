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
struct perf_counts_values {int /*<<< orphan*/  run; int /*<<< orphan*/  ena; int /*<<< orphan*/  val; } ;
struct evsel {int dummy; } ;
typedef  int /*<<< orphan*/  handler_name ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_FIELDS ; 
 int /*<<< orphan*/ * PyTuple_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyTuple_SetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int /*<<< orphan*/  _PyLong_FromLong (int) ; 
 int _PyTuple_Resize (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  call_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * get_handler (char*) ; 
 int /*<<< orphan*/  get_handler_name (char*,int,struct evsel*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  tuple_set_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_stat(struct evsel *counter, int cpu, int thread, u64 tstamp,
	     struct perf_counts_values *count)
{
	PyObject *handler, *t;
	static char handler_name[256];
	int n = 0;

	t = PyTuple_New(MAX_FIELDS);
	if (!t)
		Py_FatalError("couldn't create Python tuple");

	get_handler_name(handler_name, sizeof(handler_name),
			 counter);

	handler = get_handler(handler_name);
	if (!handler) {
		pr_debug("can't find python handler %s\n", handler_name);
		return;
	}

	PyTuple_SetItem(t, n++, _PyLong_FromLong(cpu));
	PyTuple_SetItem(t, n++, _PyLong_FromLong(thread));

	tuple_set_u64(t, n++, tstamp);
	tuple_set_u64(t, n++, count->val);
	tuple_set_u64(t, n++, count->ena);
	tuple_set_u64(t, n++, count->run);

	if (_PyTuple_Resize(&t, n) == -1)
		Py_FatalError("error resizing Python tuple");

	call_object(handler, t, handler_name);

	Py_DECREF(t);
}