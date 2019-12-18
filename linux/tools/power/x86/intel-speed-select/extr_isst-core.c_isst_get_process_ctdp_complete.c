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
struct TYPE_2__ {int /*<<< orphan*/  core_cpumask; } ;
struct isst_pkg_ctdp_level_info {int /*<<< orphan*/  core_cpumask; TYPE_1__ pbf_info; scalar_t__ pbf_support; } ;
struct isst_pkg_ctdp {int levels; struct isst_pkg_ctdp_level_info* ctdp_level; int /*<<< orphan*/  processed; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpu_set (int /*<<< orphan*/ ) ; 

void isst_get_process_ctdp_complete(int cpu, struct isst_pkg_ctdp *pkg_dev)
{
	int i;

	if (!pkg_dev->processed)
		return;

	for (i = 0; i < pkg_dev->levels; ++i) {
		struct isst_pkg_ctdp_level_info *ctdp_level;

		ctdp_level = &pkg_dev->ctdp_level[i];
		if (ctdp_level->pbf_support)
			free_cpu_set(ctdp_level->pbf_info.core_cpumask);
		free_cpu_set(ctdp_level->core_cpumask);
	}
}