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
struct pyrf_event {int dummy; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyObject_GenericGetAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_tracepoint_field (struct pyrf_event*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_tracepoint (struct pyrf_event*) ; 

__attribute__((used)) static PyObject*
pyrf_sample_event__getattro(struct pyrf_event *pevent, PyObject *attr_name)
{
	PyObject *obj = NULL;

	if (is_tracepoint(pevent))
		obj = get_tracepoint_field(pevent, attr_name);

	return obj ?: PyObject_GenericGetAttr((PyObject *) pevent, attr_name);
}