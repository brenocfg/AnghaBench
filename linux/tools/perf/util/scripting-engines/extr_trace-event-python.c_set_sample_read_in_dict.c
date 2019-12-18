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
typedef  int u64 ;
struct TYPE_7__ {int nr; int /*<<< orphan*/ * values; } ;
struct TYPE_8__ {int /*<<< orphan*/  one; TYPE_3__ group; int /*<<< orphan*/  time_running; int /*<<< orphan*/  time_enabled; } ;
struct perf_sample {TYPE_4__ read; } ;
struct TYPE_5__ {int read_format; } ;
struct TYPE_6__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int PERF_FORMAT_GROUP ; 
 int PERF_FORMAT_TOTAL_TIME_ENABLED ; 
 int PERF_FORMAT_TOTAL_TIME_RUNNING ; 
 int /*<<< orphan*/ * PyList_New (int) ; 
 int /*<<< orphan*/  PyList_SET_ITEM (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromUnsignedLongLong (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int /*<<< orphan*/ * get_sample_value_as_tuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pydict_set_item_string_decref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_sample_read_in_dict(PyObject *dict_sample,
					 struct perf_sample *sample,
					 struct evsel *evsel)
{
	u64 read_format = evsel->core.attr.read_format;
	PyObject *values;
	unsigned int i;

	if (read_format & PERF_FORMAT_TOTAL_TIME_ENABLED) {
		pydict_set_item_string_decref(dict_sample, "time_enabled",
			PyLong_FromUnsignedLongLong(sample->read.time_enabled));
	}

	if (read_format & PERF_FORMAT_TOTAL_TIME_RUNNING) {
		pydict_set_item_string_decref(dict_sample, "time_running",
			PyLong_FromUnsignedLongLong(sample->read.time_running));
	}

	if (read_format & PERF_FORMAT_GROUP)
		values = PyList_New(sample->read.group.nr);
	else
		values = PyList_New(1);

	if (!values)
		Py_FatalError("couldn't create Python list");

	if (read_format & PERF_FORMAT_GROUP) {
		for (i = 0; i < sample->read.group.nr; i++) {
			PyObject *t = get_sample_value_as_tuple(&sample->read.group.values[i]);
			PyList_SET_ITEM(values, i, t);
		}
	} else {
		PyObject *t = get_sample_value_as_tuple(&sample->read.one);
		PyList_SET_ITEM(values, 0, t);
	}
	pydict_set_item_string_decref(dict_sample, "values", values);
}