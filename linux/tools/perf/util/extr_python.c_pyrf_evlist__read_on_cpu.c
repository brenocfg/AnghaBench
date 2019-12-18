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
typedef  union perf_event {int dummy; } perf_event ;
struct evlist {int dummy; } ;
struct pyrf_evlist {struct evlist evlist; } ;
struct pyrf_event {int /*<<< orphan*/  sample; struct evsel* evsel; } ;
struct mmap {int dummy; } ;
struct evsel {int dummy; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int*,int*) ; 
 int /*<<< orphan*/ * PyErr_Format (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyExc_OSError ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 struct mmap* get_md (struct evlist*,int) ; 
 struct evsel* perf_evlist__event2evsel (struct evlist*,union perf_event*) ; 
 int perf_evsel__parse_sample (struct evsel*,union perf_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_mmap__consume (struct mmap*) ; 
 union perf_event* perf_mmap__read_event (struct mmap*) ; 
 scalar_t__ perf_mmap__read_init (struct mmap*) ; 
 int /*<<< orphan*/ * pyrf_event__new (union perf_event*) ; 

__attribute__((used)) static PyObject *pyrf_evlist__read_on_cpu(struct pyrf_evlist *pevlist,
					  PyObject *args, PyObject *kwargs)
{
	struct evlist *evlist = &pevlist->evlist;
	union perf_event *event;
	int sample_id_all = 1, cpu;
	static char *kwlist[] = { "cpu", "sample_id_all", NULL };
	struct mmap *md;
	int err;

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i|i", kwlist,
					 &cpu, &sample_id_all))
		return NULL;

	md = get_md(evlist, cpu);
	if (!md)
		return NULL;

	if (perf_mmap__read_init(md) < 0)
		goto end;

	event = perf_mmap__read_event(md);
	if (event != NULL) {
		PyObject *pyevent = pyrf_event__new(event);
		struct pyrf_event *pevent = (struct pyrf_event *)pyevent;
		struct evsel *evsel;

		if (pyevent == NULL)
			return PyErr_NoMemory();

		evsel = perf_evlist__event2evsel(evlist, event);
		if (!evsel) {
			Py_INCREF(Py_None);
			return Py_None;
		}

		pevent->evsel = evsel;

		err = perf_evsel__parse_sample(evsel, event, &pevent->sample);

		/* Consume the even only after we parsed it out. */
		perf_mmap__consume(md);

		if (err)
			return PyErr_Format(PyExc_OSError,
					    "perf: can't parse sample, err=%d", err);
		return pyevent;
	}
end:
	Py_INCREF(Py_None);
	return Py_None;
}