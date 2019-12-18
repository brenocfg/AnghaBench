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
struct perf_sample {int dummy; } ;
struct evsel {int dummy; } ;
struct addr_location {int dummy; } ;
typedef  int /*<<< orphan*/  handler_name ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_FIELDS ; 
 int /*<<< orphan*/ * PyTuple_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyTuple_SetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int _PyTuple_Resize (int /*<<< orphan*/ **,unsigned int) ; 
 int /*<<< orphan*/  call_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * get_handler (char*) ; 
 int /*<<< orphan*/ * get_perf_sample_dict (struct perf_sample*,struct evsel*,struct addr_location*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * python_process_callchain (struct perf_sample*,struct evsel*,struct addr_location*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void python_process_general_event(struct perf_sample *sample,
					 struct evsel *evsel,
					 struct addr_location *al)
{
	PyObject *handler, *t, *dict, *callchain;
	static char handler_name[64];
	unsigned n = 0;

	snprintf(handler_name, sizeof(handler_name), "%s", "process_event");

	handler = get_handler(handler_name);
	if (!handler)
		return;

	/*
	 * Use the MAX_FIELDS to make the function expandable, though
	 * currently there is only one item for the tuple.
	 */
	t = PyTuple_New(MAX_FIELDS);
	if (!t)
		Py_FatalError("couldn't create Python tuple");

	/* ip unwinding */
	callchain = python_process_callchain(sample, evsel, al);
	dict = get_perf_sample_dict(sample, evsel, al, callchain);

	PyTuple_SetItem(t, n++, dict);
	if (_PyTuple_Resize(&t, n) == -1)
		Py_FatalError("error resizing Python tuple");

	call_object(handler, t, handler_name);

	Py_DECREF(t);
}