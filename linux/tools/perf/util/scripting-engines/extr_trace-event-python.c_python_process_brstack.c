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
typedef  size_t u64 ;
struct thread {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  cpumode; struct branch_stack* branch_stack; } ;
struct branch_stack {size_t nr; TYPE_2__* entries; } ;
struct addr_location {int /*<<< orphan*/  map; } ;
struct TYPE_3__ {int /*<<< orphan*/  cycles; int /*<<< orphan*/  abort; int /*<<< orphan*/  in_tx; int /*<<< orphan*/  predicted; int /*<<< orphan*/  mispred; } ;
struct TYPE_4__ {int /*<<< orphan*/  to; int /*<<< orphan*/  from; TYPE_1__ flags; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyBool_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  PyList_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyList_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyLong_FromUnsignedLongLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int /*<<< orphan*/  _PyUnicode_FromString (char const*) ; 
 char* get_dsoname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pydict_set_item_string_decref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread__find_map_fb (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addr_location*) ; 

__attribute__((used)) static PyObject *python_process_brstack(struct perf_sample *sample,
					struct thread *thread)
{
	struct branch_stack *br = sample->branch_stack;
	PyObject *pylist;
	u64 i;

	pylist = PyList_New(0);
	if (!pylist)
		Py_FatalError("couldn't create Python list");

	if (!(br && br->nr))
		goto exit;

	for (i = 0; i < br->nr; i++) {
		PyObject *pyelem;
		struct addr_location al;
		const char *dsoname;

		pyelem = PyDict_New();
		if (!pyelem)
			Py_FatalError("couldn't create Python dictionary");

		pydict_set_item_string_decref(pyelem, "from",
		    PyLong_FromUnsignedLongLong(br->entries[i].from));
		pydict_set_item_string_decref(pyelem, "to",
		    PyLong_FromUnsignedLongLong(br->entries[i].to));
		pydict_set_item_string_decref(pyelem, "mispred",
		    PyBool_FromLong(br->entries[i].flags.mispred));
		pydict_set_item_string_decref(pyelem, "predicted",
		    PyBool_FromLong(br->entries[i].flags.predicted));
		pydict_set_item_string_decref(pyelem, "in_tx",
		    PyBool_FromLong(br->entries[i].flags.in_tx));
		pydict_set_item_string_decref(pyelem, "abort",
		    PyBool_FromLong(br->entries[i].flags.abort));
		pydict_set_item_string_decref(pyelem, "cycles",
		    PyLong_FromUnsignedLongLong(br->entries[i].flags.cycles));

		thread__find_map_fb(thread, sample->cpumode,
				    br->entries[i].from, &al);
		dsoname = get_dsoname(al.map);
		pydict_set_item_string_decref(pyelem, "from_dsoname",
					      _PyUnicode_FromString(dsoname));

		thread__find_map_fb(thread, sample->cpumode,
				    br->entries[i].to, &al);
		dsoname = get_dsoname(al.map);
		pydict_set_item_string_decref(pyelem, "to_dsoname",
					      _PyUnicode_FromString(dsoname));

		PyList_Append(pylist, pyelem);
		Py_DECREF(pyelem);
	}

exit:
	return pylist;
}