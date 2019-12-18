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
struct TYPE_3__ {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {TYPE_1__ read; } ;
struct pyrf_event {TYPE_2__ event; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * _PyUnicode_FromFormat (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *pyrf_read_event__repr(struct pyrf_event *pevent)
{
	return _PyUnicode_FromFormat("{ type: read, pid: %u, tid: %u }",
				   pevent->event.read.pid,
				   pevent->event.read.tid);
	/*
 	 * FIXME: return the array of read values,
 	 * making this method useful ;-)
 	 */
}