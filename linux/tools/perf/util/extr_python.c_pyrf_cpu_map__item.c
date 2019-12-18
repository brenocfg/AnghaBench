#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pyrf_cpu_map {TYPE_1__* cpus; } ;
struct TYPE_2__ {size_t nr; int /*<<< orphan*/ * map; } ;
typedef  size_t Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject *pyrf_cpu_map__item(PyObject *obj, Py_ssize_t i)
{
	struct pyrf_cpu_map *pcpus = (void *)obj;

	if (i >= pcpus->cpus->nr)
		return NULL;

	return Py_BuildValue("i", pcpus->cpus->map[i]);
}