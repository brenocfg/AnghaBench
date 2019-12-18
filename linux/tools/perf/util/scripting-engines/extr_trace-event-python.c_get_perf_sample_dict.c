#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct perf_sample {int raw_size; scalar_t__ raw_data; int /*<<< orphan*/  transaction; int /*<<< orphan*/  weight; int /*<<< orphan*/  addr; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  period; int /*<<< orphan*/  time; int /*<<< orphan*/  ip; int /*<<< orphan*/  cpu; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct TYPE_5__ {int /*<<< orphan*/  attr; } ;
struct evsel {TYPE_1__ core; } ;
struct addr_location {int /*<<< orphan*/  thread; TYPE_4__* sym; TYPE_3__* map; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_2__* dso; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/ * PyLong_FromUnsignedLongLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int /*<<< orphan*/ * _PyBytes_FromStringAndSize (char const*,int) ; 
 int /*<<< orphan*/ * _PyLong_FromLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _PyUnicode_FromString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evsel__name (struct evsel*) ; 
 int /*<<< orphan*/  pydict_set_item_string_decref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * python_process_brstack (struct perf_sample*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * python_process_brstacksym (struct perf_sample*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_regs_in_dict (int /*<<< orphan*/ *,struct perf_sample*,struct evsel*) ; 
 int /*<<< orphan*/  set_sample_datasrc_in_dict (int /*<<< orphan*/ *,struct perf_sample*) ; 
 int /*<<< orphan*/  set_sample_read_in_dict (int /*<<< orphan*/ *,struct perf_sample*,struct evsel*) ; 
 int /*<<< orphan*/  thread__comm_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *get_perf_sample_dict(struct perf_sample *sample,
					 struct evsel *evsel,
					 struct addr_location *al,
					 PyObject *callchain)
{
	PyObject *dict, *dict_sample, *brstack, *brstacksym;

	dict = PyDict_New();
	if (!dict)
		Py_FatalError("couldn't create Python dictionary");

	dict_sample = PyDict_New();
	if (!dict_sample)
		Py_FatalError("couldn't create Python dictionary");

	pydict_set_item_string_decref(dict, "ev_name", _PyUnicode_FromString(perf_evsel__name(evsel)));
	pydict_set_item_string_decref(dict, "attr", _PyBytes_FromStringAndSize((const char *)&evsel->core.attr, sizeof(evsel->core.attr)));

	pydict_set_item_string_decref(dict_sample, "pid",
			_PyLong_FromLong(sample->pid));
	pydict_set_item_string_decref(dict_sample, "tid",
			_PyLong_FromLong(sample->tid));
	pydict_set_item_string_decref(dict_sample, "cpu",
			_PyLong_FromLong(sample->cpu));
	pydict_set_item_string_decref(dict_sample, "ip",
			PyLong_FromUnsignedLongLong(sample->ip));
	pydict_set_item_string_decref(dict_sample, "time",
			PyLong_FromUnsignedLongLong(sample->time));
	pydict_set_item_string_decref(dict_sample, "period",
			PyLong_FromUnsignedLongLong(sample->period));
	pydict_set_item_string_decref(dict_sample, "phys_addr",
			PyLong_FromUnsignedLongLong(sample->phys_addr));
	pydict_set_item_string_decref(dict_sample, "addr",
			PyLong_FromUnsignedLongLong(sample->addr));
	set_sample_read_in_dict(dict_sample, sample, evsel);
	pydict_set_item_string_decref(dict_sample, "weight",
			PyLong_FromUnsignedLongLong(sample->weight));
	pydict_set_item_string_decref(dict_sample, "transaction",
			PyLong_FromUnsignedLongLong(sample->transaction));
	set_sample_datasrc_in_dict(dict_sample, sample);
	pydict_set_item_string_decref(dict, "sample", dict_sample);

	pydict_set_item_string_decref(dict, "raw_buf", _PyBytes_FromStringAndSize(
			(const char *)sample->raw_data, sample->raw_size));
	pydict_set_item_string_decref(dict, "comm",
			_PyUnicode_FromString(thread__comm_str(al->thread)));
	if (al->map) {
		pydict_set_item_string_decref(dict, "dso",
			_PyUnicode_FromString(al->map->dso->name));
	}
	if (al->sym) {
		pydict_set_item_string_decref(dict, "symbol",
			_PyUnicode_FromString(al->sym->name));
	}

	pydict_set_item_string_decref(dict, "callchain", callchain);

	brstack = python_process_brstack(sample, al->thread);
	pydict_set_item_string_decref(dict, "brstack", brstack);

	brstacksym = python_process_brstacksym(sample, al->thread);
	pydict_set_item_string_decref(dict, "brstacksym", brstacksym);

	set_regs_in_dict(dict, sample, evsel);

	return dict;
}