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
struct isst_pkg_ctdp_level_info {int processed; int level; int control_cpu; int pbf_found; int /*<<< orphan*/  fact_info; scalar_t__ fact_support; int /*<<< orphan*/  pbf_info; scalar_t__ pbf_support; int /*<<< orphan*/  trl_avx_512_active_cores; int /*<<< orphan*/  trl_avx_active_cores; int /*<<< orphan*/  trl_sse_active_cores; int /*<<< orphan*/  buckets_info; int /*<<< orphan*/  core_cpumask; int /*<<< orphan*/  core_cpumask_size; int /*<<< orphan*/  die_id; int /*<<< orphan*/  pkg_id; } ;
struct isst_pkg_ctdp {int processed; int levels; struct isst_pkg_ctdp_level_info* ctdp_level; int /*<<< orphan*/  current_level; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_cpu_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_printf (char*,int,int,...) ; 
 int /*<<< orphan*/  get_physical_die_id (int) ; 
 int /*<<< orphan*/  get_physical_package_id (int) ; 
 int isst_get_coremask_info (int,int,struct isst_pkg_ctdp_level_info*) ; 
 int isst_get_ctdp_control (int,int,struct isst_pkg_ctdp_level_info*) ; 
 int isst_get_ctdp_levels (int,struct isst_pkg_ctdp*) ; 
 int isst_get_fact_info (int,int,int /*<<< orphan*/ *) ; 
 int isst_get_get_trl (int,int,int,int /*<<< orphan*/ ) ; 
 int isst_get_pbf_info (int,int,int /*<<< orphan*/ *) ; 
 int isst_get_pwr_info (int,int,struct isst_pkg_ctdp_level_info*) ; 
 int isst_get_tdp_info (int,int,struct isst_pkg_ctdp_level_info*) ; 
 int isst_get_tjmax_info (int,int,struct isst_pkg_ctdp_level_info*) ; 
 int isst_get_trl_bucket_info (int,int /*<<< orphan*/ *) ; 

int isst_get_process_ctdp(int cpu, int tdp_level, struct isst_pkg_ctdp *pkg_dev)
{
	int i, ret;

	if (pkg_dev->processed)
		return 0;

	ret = isst_get_ctdp_levels(cpu, pkg_dev);
	if (ret)
		return ret;

	debug_printf("cpu: %d ctdp enable:%d current level: %d levels:%d\n",
		     cpu, pkg_dev->enabled, pkg_dev->current_level,
		     pkg_dev->levels);

	for (i = 0; i <= pkg_dev->levels; ++i) {
		struct isst_pkg_ctdp_level_info *ctdp_level;

		if (tdp_level != 0xff && i != tdp_level)
			continue;

		debug_printf("cpu:%d Get Information for TDP level:%d\n", cpu,
			     i);
		ctdp_level = &pkg_dev->ctdp_level[i];

		ctdp_level->processed = 1;
		ctdp_level->level = i;
		ctdp_level->control_cpu = cpu;
		ctdp_level->pkg_id = get_physical_package_id(cpu);
		ctdp_level->die_id = get_physical_die_id(cpu);

		ret = isst_get_ctdp_control(cpu, i, ctdp_level);
		if (ret)
			return ret;

		ret = isst_get_tdp_info(cpu, i, ctdp_level);
		if (ret)
			return ret;

		ret = isst_get_pwr_info(cpu, i, ctdp_level);
		if (ret)
			return ret;

		ret = isst_get_tjmax_info(cpu, i, ctdp_level);
		if (ret)
			return ret;

		ctdp_level->core_cpumask_size =
			alloc_cpu_set(&ctdp_level->core_cpumask);
		ret = isst_get_coremask_info(cpu, i, ctdp_level);
		if (ret)
			return ret;

		ret = isst_get_trl_bucket_info(cpu, &ctdp_level->buckets_info);
		if (ret)
			return ret;

		ret = isst_get_get_trl(cpu, i, 0,
				       ctdp_level->trl_sse_active_cores);
		if (ret)
			return ret;

		ret = isst_get_get_trl(cpu, i, 1,
				       ctdp_level->trl_avx_active_cores);
		if (ret)
			return ret;

		ret = isst_get_get_trl(cpu, i, 2,
				       ctdp_level->trl_avx_512_active_cores);
		if (ret)
			return ret;

		if (ctdp_level->pbf_support) {
			ret = isst_get_pbf_info(cpu, i, &ctdp_level->pbf_info);
			if (!ret)
				ctdp_level->pbf_found = 1;
		}

		if (ctdp_level->fact_support) {
			ret = isst_get_fact_info(cpu, i,
						 &ctdp_level->fact_info);
			if (ret)
				return ret;
		}
	}

	pkg_dev->processed = 1;

	return 0;
}