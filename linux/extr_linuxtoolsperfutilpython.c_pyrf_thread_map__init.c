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
struct pyrf_thread_map {int /*<<< orphan*/ * threads; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int*,int*,int*) ; 
 int UINT_MAX ; 
 int /*<<< orphan*/ * thread_map__new (int,int,int) ; 

__attribute__((used)) static int pyrf_thread_map__init(struct pyrf_thread_map *pthreads,
				 PyObject *args, PyObject *kwargs)
{
	static char *kwlist[] = { "pid", "tid", "uid", NULL };
	int pid = -1, tid = -1, uid = UINT_MAX;

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|iii",
					 kwlist, &pid, &tid, &uid))
		return -1;

	pthreads->threads = thread_map__new(pid, tid, uid);
	if (pthreads->threads == NULL)
		return -1;
	return 0;
}