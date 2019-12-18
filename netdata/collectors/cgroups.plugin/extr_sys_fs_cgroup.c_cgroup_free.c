#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {struct cgroup* filename; } ;
struct TYPE_17__ {struct cgroup* filename; } ;
struct TYPE_16__ {struct cgroup* filename; } ;
struct TYPE_15__ {struct cgroup* filename; } ;
struct TYPE_14__ {struct cgroup* filename; } ;
struct TYPE_13__ {struct cgroup* filename; } ;
struct TYPE_12__ {struct cgroup* filename_msw_usage_in_bytes; struct cgroup* filename_usage_in_bytes; struct cgroup* filename_failcnt; struct cgroup* filename_detailed; int /*<<< orphan*/  arl_base; } ;
struct TYPE_11__ {struct cgroup* filename; struct cgroup* cpu_percpu; } ;
struct TYPE_10__ {struct cgroup* filename; } ;
struct cgroup {struct cgroup* chart_title; struct cgroup* chart_id; struct cgroup* id; TYPE_9__ io_queued; TYPE_8__ io_merged; TYPE_7__ throttle_io_serviced; TYPE_6__ throttle_io_service_bytes; TYPE_5__ io_serviced; TYPE_4__ io_service_bytes; TYPE_3__ memory; TYPE_2__ cpuacct_usage; TYPE_1__ cpuacct_stat; struct cgroup* filename_memoryswap_limit; struct cgroup* filename_memory_limit; struct cgroup* filename_cpu_cfs_quota; struct cgroup* filename_cpu_cfs_period; struct cgroup* filename_cpuset_cpus; scalar_t__ st_merged_ops; scalar_t__ st_queued_ops; scalar_t__ st_throttle_serviced_ops; scalar_t__ st_throttle_io; scalar_t__ st_serviced_ops; scalar_t__ st_io; scalar_t__ st_mem_failcnt; scalar_t__ st_mem_usage_limit; scalar_t__ st_mem_usage; scalar_t__ st_pgfaults; scalar_t__ st_mem_activity; scalar_t__ st_writeback; scalar_t__ st_mem; scalar_t__ st_cpu_per_core; scalar_t__ st_cpu_limit; scalar_t__ st_cpu; scalar_t__ available; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CGROUP ; 
 int /*<<< orphan*/  arl_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_root_count ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,struct cgroup*,struct cgroup*,char*,char*) ; 
 int /*<<< orphan*/  free_cgroup_network_interfaces (struct cgroup*) ; 
 int /*<<< orphan*/  freez (struct cgroup*) ; 
 int /*<<< orphan*/  rrdset_is_obsolete (scalar_t__) ; 

__attribute__((used)) static inline void cgroup_free(struct cgroup *cg) {
    debug(D_CGROUP, "Removing cgroup '%s' with chart id '%s' (was %s and %s)", cg->id, cg->chart_id, (cg->enabled)?"enabled":"disabled", (cg->available)?"available":"not available");

    if(cg->st_cpu)                   rrdset_is_obsolete(cg->st_cpu);
    if(cg->st_cpu_limit)             rrdset_is_obsolete(cg->st_cpu_limit);
    if(cg->st_cpu_per_core)          rrdset_is_obsolete(cg->st_cpu_per_core);
    if(cg->st_mem)                   rrdset_is_obsolete(cg->st_mem);
    if(cg->st_writeback)             rrdset_is_obsolete(cg->st_writeback);
    if(cg->st_mem_activity)          rrdset_is_obsolete(cg->st_mem_activity);
    if(cg->st_pgfaults)              rrdset_is_obsolete(cg->st_pgfaults);
    if(cg->st_mem_usage)             rrdset_is_obsolete(cg->st_mem_usage);
    if(cg->st_mem_usage_limit)       rrdset_is_obsolete(cg->st_mem_usage_limit);
    if(cg->st_mem_failcnt)           rrdset_is_obsolete(cg->st_mem_failcnt);
    if(cg->st_io)                    rrdset_is_obsolete(cg->st_io);
    if(cg->st_serviced_ops)          rrdset_is_obsolete(cg->st_serviced_ops);
    if(cg->st_throttle_io)           rrdset_is_obsolete(cg->st_throttle_io);
    if(cg->st_throttle_serviced_ops) rrdset_is_obsolete(cg->st_throttle_serviced_ops);
    if(cg->st_queued_ops)            rrdset_is_obsolete(cg->st_queued_ops);
    if(cg->st_merged_ops)            rrdset_is_obsolete(cg->st_merged_ops);

    freez(cg->filename_cpuset_cpus);
    freez(cg->filename_cpu_cfs_period);
    freez(cg->filename_cpu_cfs_quota);
    freez(cg->filename_memory_limit);
    freez(cg->filename_memoryswap_limit);

    free_cgroup_network_interfaces(cg);

    freez(cg->cpuacct_usage.cpu_percpu);

    freez(cg->cpuacct_stat.filename);
    freez(cg->cpuacct_usage.filename);

    arl_free(cg->memory.arl_base);
    freez(cg->memory.filename_detailed);
    freez(cg->memory.filename_failcnt);
    freez(cg->memory.filename_usage_in_bytes);
    freez(cg->memory.filename_msw_usage_in_bytes);

    freez(cg->io_service_bytes.filename);
    freez(cg->io_serviced.filename);

    freez(cg->throttle_io_service_bytes.filename);
    freez(cg->throttle_io_serviced.filename);

    freez(cg->io_merged.filename);
    freez(cg->io_queued.filename);

    freez(cg->id);
    freez(cg->chart_id);
    freez(cg->chart_title);

    freez(cg);

    cgroup_root_count--;
}