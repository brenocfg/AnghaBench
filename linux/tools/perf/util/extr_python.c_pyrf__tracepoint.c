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
struct tep_event {int id; } ;
struct pyrf_evsel {int dummy; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tep_event*) ; 
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,char**,char**) ; 
 int /*<<< orphan*/ * _PyLong_FromLong (int) ; 
 struct tep_event* trace_event__tp_format (char*,char*) ; 

__attribute__((used)) static PyObject *pyrf__tracepoint(struct pyrf_evsel *pevsel,
				  PyObject *args, PyObject *kwargs)
{
	struct tep_event *tp_format;
	static char *kwlist[] = { "sys", "name", NULL };
	char *sys  = NULL;
	char *name = NULL;

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|ss", kwlist,
					 &sys, &name))
		return NULL;

	tp_format = trace_event__tp_format(sys, name);
	if (IS_ERR(tp_format))
		return _PyLong_FromLong(-1);

	return _PyLong_FromLong(tp_format->id);
}