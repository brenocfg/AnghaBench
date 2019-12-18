#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int misc; } ;
struct TYPE_4__ {int /*<<< orphan*/  next_prev_tid; int /*<<< orphan*/  next_prev_pid; } ;
struct TYPE_6__ {TYPE_2__ header; TYPE_1__ context_switch; } ;
struct pyrf_event {TYPE_3__ event; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int PERF_RECORD_MISC_SWITCH_OUT ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/ * _PyUnicode_FromString (char*) ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static PyObject *pyrf_context_switch_event__repr(struct pyrf_event *pevent)
{
	PyObject *ret;
	char *s;

	if (asprintf(&s, "{ type: context_switch, next_prev_pid: %u, next_prev_tid: %u, switch_out: %u }",
		     pevent->event.context_switch.next_prev_pid,
		     pevent->event.context_switch.next_prev_tid,
		     !!(pevent->event.header.misc & PERF_RECORD_MISC_SWITCH_OUT)) < 0) {
		ret = PyErr_NoMemory();
	} else {
		ret = _PyUnicode_FromString(s);
		free(s);
	}
	return ret;
}