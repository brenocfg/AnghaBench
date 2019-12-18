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
struct pyrf_cpu_map {int /*<<< orphan*/ * cpus; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,char**) ; 
 int /*<<< orphan*/ * perf_cpu_map__new (char*) ; 

__attribute__((used)) static int pyrf_cpu_map__init(struct pyrf_cpu_map *pcpus,
			      PyObject *args, PyObject *kwargs)
{
	static char *kwlist[] = { "cpustr", NULL };
	char *cpustr = NULL;

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|s",
					 kwlist, &cpustr))
		return -1;

	pcpus->cpus = perf_cpu_map__new(cpustr);
	if (pcpus->cpus == NULL)
		return -1;
	return 0;
}