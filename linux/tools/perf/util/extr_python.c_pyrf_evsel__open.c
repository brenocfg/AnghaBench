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
struct pyrf_thread_map {struct perf_thread_map* threads; } ;
struct TYPE_3__ {int inherit; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;
struct pyrf_evsel {struct evsel evsel; } ;
struct pyrf_cpu_map {struct perf_cpu_map* cpus; } ;
struct perf_thread_map {int dummy; } ;
struct perf_cpu_map {int dummy; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*,int*) ; 
 int /*<<< orphan*/  PyErr_SetFromErrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_OSError ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 scalar_t__ evsel__open (struct evsel*,struct perf_cpu_map*,struct perf_thread_map*) ; 

__attribute__((used)) static PyObject *pyrf_evsel__open(struct pyrf_evsel *pevsel,
				  PyObject *args, PyObject *kwargs)
{
	struct evsel *evsel = &pevsel->evsel;
	struct perf_cpu_map *cpus = NULL;
	struct perf_thread_map *threads = NULL;
	PyObject *pcpus = NULL, *pthreads = NULL;
	int group = 0, inherit = 0;
	static char *kwlist[] = { "cpus", "threads", "group", "inherit", NULL };

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|OOii", kwlist,
					 &pcpus, &pthreads, &group, &inherit))
		return NULL;

	if (pthreads != NULL)
		threads = ((struct pyrf_thread_map *)pthreads)->threads;

	if (pcpus != NULL)
		cpus = ((struct pyrf_cpu_map *)pcpus)->cpus;

	evsel->core.attr.inherit = inherit;
	/*
	 * This will group just the fds for this single evsel, to group
	 * multiple events, use evlist.open().
	 */
	if (evsel__open(evsel, cpus, threads) < 0) {
		PyErr_SetFromErrno(PyExc_OSError);
		return NULL;
	}

	Py_INCREF(Py_None);
	return Py_None;
}