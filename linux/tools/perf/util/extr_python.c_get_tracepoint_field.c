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
struct tep_format_field {int dummy; } ;
struct tep_event {int dummy; } ;
struct pyrf_event {struct evsel* evsel; } ;
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {struct tep_event* tp_format; TYPE_2__ core; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyObject_Str (int /*<<< orphan*/ *) ; 
 char* _PyUnicode_AsString (int /*<<< orphan*/ ) ; 
 struct tep_format_field* tep_find_any_field (struct tep_event*,char const*) ; 
 struct tep_event* trace_event__tp_format_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tracepoint_field (struct pyrf_event*,struct tep_format_field*) ; 

__attribute__((used)) static PyObject*
get_tracepoint_field(struct pyrf_event *pevent, PyObject *attr_name)
{
	const char *str = _PyUnicode_AsString(PyObject_Str(attr_name));
	struct evsel *evsel = pevent->evsel;
	struct tep_format_field *field;

	if (!evsel->tp_format) {
		struct tep_event *tp_format;

		tp_format = trace_event__tp_format_id(evsel->core.attr.config);
		if (!tp_format)
			return NULL;

		evsel->tp_format = tp_format;
	}

	field = tep_find_any_field(evsel->tp_format, str);
	if (!field)
		return NULL;

	return tracepoint_field(pevent, field);
}