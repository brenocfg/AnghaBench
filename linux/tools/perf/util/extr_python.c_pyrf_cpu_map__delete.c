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
struct pyrf_cpu_map {int /*<<< orphan*/  cpus; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 TYPE_1__* Py_TYPE (struct pyrf_cpu_map*) ; 
 int /*<<< orphan*/  perf_cpu_map__put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pyrf_cpu_map__delete(struct pyrf_cpu_map *pcpus)
{
	perf_cpu_map__put(pcpus->cpus);
	Py_TYPE(pcpus)->tp_free((PyObject*)pcpus);
}