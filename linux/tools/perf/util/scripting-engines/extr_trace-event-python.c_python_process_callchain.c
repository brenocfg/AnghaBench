#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_sample {int /*<<< orphan*/  callchain; } ;
struct evsel {int dummy; } ;
struct callchain_cursor_node {scalar_t__ map; TYPE_1__* sym; int /*<<< orphan*/  ip; } ;
struct addr_location {int /*<<< orphan*/  thread; } ;
struct TYPE_4__ {int /*<<< orphan*/  use_callchain; } ;
struct TYPE_3__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  binding; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  PyList_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyList_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyLong_FromUnsignedLongLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int /*<<< orphan*/ * _PyLong_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _PyUnicode_FromString (char const*) ; 
 int /*<<< orphan*/ * _PyUnicode_FromStringAndSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callchain_cursor ; 
 int /*<<< orphan*/  callchain_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callchain_cursor_commit (int /*<<< orphan*/ *) ; 
 struct callchain_cursor_node* callchain_cursor_current (int /*<<< orphan*/ *) ; 
 char* get_dsoname (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pydict_set_item_string_decref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scripting_max_stack ; 
 TYPE_2__ symbol_conf ; 
 scalar_t__ thread__resolve_callchain (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct evsel*,struct perf_sample*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *python_process_callchain(struct perf_sample *sample,
					 struct evsel *evsel,
					 struct addr_location *al)
{
	PyObject *pylist;

	pylist = PyList_New(0);
	if (!pylist)
		Py_FatalError("couldn't create Python list");

	if (!symbol_conf.use_callchain || !sample->callchain)
		goto exit;

	if (thread__resolve_callchain(al->thread, &callchain_cursor, evsel,
				      sample, NULL, NULL,
				      scripting_max_stack) != 0) {
		pr_err("Failed to resolve callchain. Skipping\n");
		goto exit;
	}
	callchain_cursor_commit(&callchain_cursor);


	while (1) {
		PyObject *pyelem;
		struct callchain_cursor_node *node;
		node = callchain_cursor_current(&callchain_cursor);
		if (!node)
			break;

		pyelem = PyDict_New();
		if (!pyelem)
			Py_FatalError("couldn't create Python dictionary");


		pydict_set_item_string_decref(pyelem, "ip",
				PyLong_FromUnsignedLongLong(node->ip));

		if (node->sym) {
			PyObject *pysym  = PyDict_New();
			if (!pysym)
				Py_FatalError("couldn't create Python dictionary");
			pydict_set_item_string_decref(pysym, "start",
					PyLong_FromUnsignedLongLong(node->sym->start));
			pydict_set_item_string_decref(pysym, "end",
					PyLong_FromUnsignedLongLong(node->sym->end));
			pydict_set_item_string_decref(pysym, "binding",
					_PyLong_FromLong(node->sym->binding));
			pydict_set_item_string_decref(pysym, "name",
					_PyUnicode_FromStringAndSize(node->sym->name,
							node->sym->namelen));
			pydict_set_item_string_decref(pyelem, "sym", pysym);
		}

		if (node->map) {
			const char *dsoname = get_dsoname(node->map);

			pydict_set_item_string_decref(pyelem, "dso",
					_PyUnicode_FromString(dsoname));
		}

		callchain_cursor_advance(&callchain_cursor);
		PyList_Append(pylist, pyelem);
		Py_DECREF(pyelem);
	}

exit:
	return pylist;
}