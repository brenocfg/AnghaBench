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
struct stat {int dummy; } ;
struct TYPE_18__ {void* filename_msw_usage_in_bytes; scalar_t__ enabled_msw_usage_in_bytes; void* filename_usage_in_bytes; void* enabled_usage_in_bytes; void* filename_detailed; scalar_t__ enabled_detailed; void* filename_failcnt; void* enabled_failcnt; } ;
struct TYPE_17__ {void* filename; void* enabled; } ;
struct TYPE_16__ {void* filename; void* enabled; } ;
struct TYPE_15__ {void* enabled; void* filename; } ;
struct TYPE_14__ {void* filename; void* enabled; } ;
struct TYPE_13__ {void* filename; void* enabled; } ;
struct TYPE_12__ {void* filename; void* enabled; } ;
struct TYPE_11__ {void* filename; void* enabled; } ;
struct TYPE_10__ {void* filename; void* enabled; } ;
struct cgroup {int pending_renames; int options; int /*<<< orphan*/  id; TYPE_9__ memory; void* filename_memoryswap_limit; void* filename_memory_limit; TYPE_8__ cpuacct_stat; int /*<<< orphan*/ * filename_cpu_cfs_quota; int /*<<< orphan*/ * filename_cpu_cfs_period; int /*<<< orphan*/ * filename_cpuset_cpus; TYPE_7__ io_service_bytes; TYPE_6__ io_serviced; TYPE_5__ io_queued; TYPE_4__ io_merged; TYPE_3__ throttle_io_serviced; TYPE_2__ throttle_io_service_bytes; TYPE_1__ cpuacct_usage; int /*<<< orphan*/  available; struct cgroup* next; } ;

/* Variables and functions */
 int CGROUP_OPTIONS_SYSTEM_SLICE_SERVICE ; 
 scalar_t__ CONFIG_BOOLEAN_AUTO ; 
 void* CONFIG_BOOLEAN_NO ; 
 scalar_t__ CONFIG_BOOLEAN_YES ; 
 int /*<<< orphan*/  D_CGROUP ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  cgroup_blkio_base ; 
 int /*<<< orphan*/  cgroup_cpuacct_base ; 
 int /*<<< orphan*/  cgroup_cpuset_base ; 
 int /*<<< orphan*/  cgroup_devices_base ; 
 void* cgroup_enable_blkio_io ; 
 void* cgroup_enable_blkio_merged_ops ; 
 void* cgroup_enable_blkio_ops ; 
 void* cgroup_enable_blkio_queued_ops ; 
 void* cgroup_enable_blkio_throttle_io ; 
 void* cgroup_enable_blkio_throttle_ops ; 
 void* cgroup_enable_cpuacct_stat ; 
 void* cgroup_enable_cpuacct_usage ; 
 scalar_t__ cgroup_enable_detailed_memory ; 
 void* cgroup_enable_memory ; 
 void* cgroup_enable_memory_failcnt ; 
 scalar_t__ cgroup_enable_swap ; 
 scalar_t__ cgroup_enable_systemd_services_detailed_memory ; 
 int /*<<< orphan*/  cgroup_memory_base ; 
 struct cgroup* cgroup_root ; 
 scalar_t__ cgroup_search_in_devices ; 
 int /*<<< orphan*/  cgroup_unified_base ; 
 int cgroup_unified_exist ; 
 int /*<<< orphan*/  cgroup_use_unified_cgroups ; 
 scalar_t__ cgroup_used_memory_without_cache ; 
 int /*<<< orphan*/  cleanup_all_cgroups () ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  error (char*) ; 
 int find_dir_in_subdirs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  found_subdir_in_dir ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mark_all_cgroups_as_not_available () ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stat (char*,struct stat*) ; 
 void* strdupz (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void find_all_cgroups() {
    debug(D_CGROUP, "searching for cgroups");

    mark_all_cgroups_as_not_available();
    if(!cgroup_use_unified_cgroups) {
        if(cgroup_enable_cpuacct_stat || cgroup_enable_cpuacct_usage) {
            if(find_dir_in_subdirs(cgroup_cpuacct_base, NULL, found_subdir_in_dir) == -1) {
                cgroup_enable_cpuacct_stat =
                cgroup_enable_cpuacct_usage = CONFIG_BOOLEAN_NO;
                error("CGROUP: disabled cpu statistics.");
            }
        }

        if(cgroup_enable_blkio_io || cgroup_enable_blkio_ops || cgroup_enable_blkio_throttle_io || cgroup_enable_blkio_throttle_ops || cgroup_enable_blkio_merged_ops || cgroup_enable_blkio_queued_ops) {
            if(find_dir_in_subdirs(cgroup_blkio_base, NULL, found_subdir_in_dir) == -1) {
                cgroup_enable_blkio_io =
                cgroup_enable_blkio_ops =
                cgroup_enable_blkio_throttle_io =
                cgroup_enable_blkio_throttle_ops =
                cgroup_enable_blkio_merged_ops =
                cgroup_enable_blkio_queued_ops = CONFIG_BOOLEAN_NO;
                error("CGROUP: disabled blkio statistics.");
            }
        }

        if(cgroup_enable_memory || cgroup_enable_detailed_memory || cgroup_enable_swap || cgroup_enable_memory_failcnt) {
            if(find_dir_in_subdirs(cgroup_memory_base, NULL, found_subdir_in_dir) == -1) {
                cgroup_enable_memory =
                cgroup_enable_detailed_memory =
                cgroup_enable_swap =
                cgroup_enable_memory_failcnt = CONFIG_BOOLEAN_NO;
                error("CGROUP: disabled memory statistics.");
            }
        }

        if(cgroup_search_in_devices) {
            if(find_dir_in_subdirs(cgroup_devices_base, NULL, found_subdir_in_dir) == -1) {
                cgroup_search_in_devices = 0;
                error("CGROUP: disabled devices statistics.");
            }
        }
    }
    else {
        if (find_dir_in_subdirs(cgroup_unified_base, NULL, found_subdir_in_dir) == -1) {
            cgroup_unified_exist = CONFIG_BOOLEAN_NO;
            error("CGROUP: disabled unified cgroups statistics.");
        }
    }

    // remove any non-existing cgroups
    cleanup_all_cgroups();

    struct cgroup *cg;
    struct stat buf;
    for(cg = cgroup_root; cg ; cg = cg->next) {
        // fprintf(stderr, " >>> CGROUP '%s' (%u - %s) with name '%s'\n", cg->id, cg->hash, cg->available?"available":"stopped", cg->name);

        if(unlikely(cg->pending_renames))
            cg->pending_renames--;

        if(unlikely(!cg->available || cg->pending_renames))
            continue;

        debug(D_CGROUP, "checking paths for cgroup '%s'", cg->id);

        // check for newly added cgroups
        // and update the filenames they read
        char filename[FILENAME_MAX + 1];
        if(!cgroup_use_unified_cgroups) {
            if(unlikely(cgroup_enable_cpuacct_stat && !cg->cpuacct_stat.filename)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/cpuacct.stat", cgroup_cpuacct_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->cpuacct_stat.filename = strdupz(filename);
                    cg->cpuacct_stat.enabled = cgroup_enable_cpuacct_stat;
                    snprintfz(filename, FILENAME_MAX, "%s%s/cpuset.cpus", cgroup_cpuset_base, cg->id);
                    cg->filename_cpuset_cpus = strdupz(filename);
                    snprintfz(filename, FILENAME_MAX, "%s%s/cpu.cfs_period_us", cgroup_cpuacct_base, cg->id);
                    cg->filename_cpu_cfs_period = strdupz(filename);
                    snprintfz(filename, FILENAME_MAX, "%s%s/cpu.cfs_quota_us", cgroup_cpuacct_base, cg->id);
                    cg->filename_cpu_cfs_quota = strdupz(filename);
                    debug(D_CGROUP, "cpuacct.stat filename for cgroup '%s': '%s'", cg->id, cg->cpuacct_stat.filename);
                }
                else
                    debug(D_CGROUP, "cpuacct.stat file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_cpuacct_usage && !cg->cpuacct_usage.filename && !(cg->options & CGROUP_OPTIONS_SYSTEM_SLICE_SERVICE))) {
                snprintfz(filename, FILENAME_MAX, "%s%s/cpuacct.usage_percpu", cgroup_cpuacct_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->cpuacct_usage.filename = strdupz(filename);
                    cg->cpuacct_usage.enabled = cgroup_enable_cpuacct_usage;
                    debug(D_CGROUP, "cpuacct.usage_percpu filename for cgroup '%s': '%s'", cg->id, cg->cpuacct_usage.filename);
                }
                else
                    debug(D_CGROUP, "cpuacct.usage_percpu file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely((cgroup_enable_detailed_memory || cgroup_used_memory_without_cache) && !cg->memory.filename_detailed && (cgroup_used_memory_without_cache || cgroup_enable_systemd_services_detailed_memory || !(cg->options & CGROUP_OPTIONS_SYSTEM_SLICE_SERVICE)))) {
                snprintfz(filename, FILENAME_MAX, "%s%s/memory.stat", cgroup_memory_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->memory.filename_detailed = strdupz(filename);
                    cg->memory.enabled_detailed = (cgroup_enable_detailed_memory == CONFIG_BOOLEAN_YES)?CONFIG_BOOLEAN_YES:CONFIG_BOOLEAN_AUTO;
                    debug(D_CGROUP, "memory.stat filename for cgroup '%s': '%s'", cg->id, cg->memory.filename_detailed);
                }
                else
                    debug(D_CGROUP, "memory.stat file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_memory && !cg->memory.filename_usage_in_bytes)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/memory.usage_in_bytes", cgroup_memory_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->memory.filename_usage_in_bytes = strdupz(filename);
                    cg->memory.enabled_usage_in_bytes = cgroup_enable_memory;
                    debug(D_CGROUP, "memory.usage_in_bytes filename for cgroup '%s': '%s'", cg->id, cg->memory.filename_usage_in_bytes);
                    snprintfz(filename, FILENAME_MAX, "%s%s/memory.limit_in_bytes", cgroup_memory_base, cg->id);
                    cg->filename_memory_limit = strdupz(filename);
                }
                else
                    debug(D_CGROUP, "memory.usage_in_bytes file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_swap && !cg->memory.filename_msw_usage_in_bytes)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/memory.memsw.usage_in_bytes", cgroup_memory_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->memory.filename_msw_usage_in_bytes = strdupz(filename);
                    cg->memory.enabled_msw_usage_in_bytes = cgroup_enable_swap;
                    snprintfz(filename, FILENAME_MAX, "%s%s/memory.memsw.limit_in_bytes", cgroup_memory_base, cg->id);
                    cg->filename_memoryswap_limit = strdupz(filename);
                    debug(D_CGROUP, "memory.msw_usage_in_bytes filename for cgroup '%s': '%s'", cg->id, cg->memory.filename_msw_usage_in_bytes);
                }
                else
                    debug(D_CGROUP, "memory.msw_usage_in_bytes file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_memory_failcnt && !cg->memory.filename_failcnt)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/memory.failcnt", cgroup_memory_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->memory.filename_failcnt = strdupz(filename);
                    cg->memory.enabled_failcnt = cgroup_enable_memory_failcnt;
                    debug(D_CGROUP, "memory.failcnt filename for cgroup '%s': '%s'", cg->id, cg->memory.filename_failcnt);
                }
                else
                    debug(D_CGROUP, "memory.failcnt file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_blkio_io && !cg->io_service_bytes.filename)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/blkio.io_service_bytes", cgroup_blkio_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->io_service_bytes.filename = strdupz(filename);
                    cg->io_service_bytes.enabled = cgroup_enable_blkio_io;
                    debug(D_CGROUP, "io_service_bytes filename for cgroup '%s': '%s'", cg->id, cg->io_service_bytes.filename);
                }
                else
                    debug(D_CGROUP, "io_service_bytes file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_blkio_ops && !cg->io_serviced.filename)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/blkio.io_serviced", cgroup_blkio_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->io_serviced.filename = strdupz(filename);
                    cg->io_serviced.enabled = cgroup_enable_blkio_ops;
                    debug(D_CGROUP, "io_serviced filename for cgroup '%s': '%s'", cg->id, cg->io_serviced.filename);
                }
                else
                    debug(D_CGROUP, "io_serviced file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_blkio_throttle_io && !cg->throttle_io_service_bytes.filename)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/blkio.throttle.io_service_bytes", cgroup_blkio_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->throttle_io_service_bytes.filename = strdupz(filename);
                    cg->throttle_io_service_bytes.enabled = cgroup_enable_blkio_throttle_io;
                    debug(D_CGROUP, "throttle_io_service_bytes filename for cgroup '%s': '%s'", cg->id, cg->throttle_io_service_bytes.filename);
                }
                else
                    debug(D_CGROUP, "throttle_io_service_bytes file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_blkio_throttle_ops && !cg->throttle_io_serviced.filename)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/blkio.throttle.io_serviced", cgroup_blkio_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->throttle_io_serviced.filename = strdupz(filename);
                    cg->throttle_io_serviced.enabled = cgroup_enable_blkio_throttle_ops;
                    debug(D_CGROUP, "throttle_io_serviced filename for cgroup '%s': '%s'", cg->id, cg->throttle_io_serviced.filename);
                }
                else
                    debug(D_CGROUP, "throttle_io_serviced file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_blkio_merged_ops && !cg->io_merged.filename)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/blkio.io_merged", cgroup_blkio_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->io_merged.filename = strdupz(filename);
                    cg->io_merged.enabled = cgroup_enable_blkio_merged_ops;
                    debug(D_CGROUP, "io_merged filename for cgroup '%s': '%s'", cg->id, cg->io_merged.filename);
                }
                else
                    debug(D_CGROUP, "io_merged file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_blkio_queued_ops && !cg->io_queued.filename)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/blkio.io_queued", cgroup_blkio_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->io_queued.filename = strdupz(filename);
                    cg->io_queued.enabled = cgroup_enable_blkio_queued_ops;
                    debug(D_CGROUP, "io_queued filename for cgroup '%s': '%s'", cg->id, cg->io_queued.filename);
                }
                else
                    debug(D_CGROUP, "io_queued file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }
        }
        else if(likely(cgroup_unified_exist)) {
            if(unlikely(cgroup_enable_blkio_io && !cg->io_service_bytes.filename)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/io.stat", cgroup_unified_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->io_service_bytes.filename = strdupz(filename);
                    cg->io_service_bytes.enabled = cgroup_enable_blkio_io;
                    debug(D_CGROUP, "io.stat filename for unified cgroup '%s': '%s'", cg->id, cg->io_service_bytes.filename);
                } else
                    debug(D_CGROUP, "io.stat file for unified cgroup '%s': '%s' does not exist.", cg->id, filename);
            }
            if (unlikely(cgroup_enable_blkio_ops && !cg->io_serviced.filename)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/io.stat", cgroup_unified_base, cg->id);
                if (likely(stat(filename, &buf) != -1)) {
                    cg->io_serviced.filename = strdupz(filename);
                    cg->io_serviced.enabled = cgroup_enable_blkio_ops;
                    debug(D_CGROUP, "io.stat filename for unified cgroup '%s': '%s'", cg->id, cg->io_service_bytes.filename);
                } else
                    debug(D_CGROUP, "io.stat file for unified cgroup '%s': '%s' does not exist.", cg->id, filename);
            }
            if(unlikely(cgroup_enable_cpuacct_stat && !cg->cpuacct_stat.filename)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/cpu.stat", cgroup_unified_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->cpuacct_stat.filename = strdupz(filename);
                    cg->cpuacct_stat.enabled = cgroup_enable_cpuacct_stat;
                    cg->filename_cpuset_cpus = NULL;
                    cg->filename_cpu_cfs_period = NULL;
                    cg->filename_cpu_cfs_quota = NULL;
                    debug(D_CGROUP, "cpu.stat filename for unified cgroup '%s': '%s'", cg->id, cg->cpuacct_stat.filename);
                }
                else
                    debug(D_CGROUP, "cpu.stat file for unified cgroup '%s': '%s' does not exist.", cg->id, filename);
            }
            if(unlikely((cgroup_enable_detailed_memory || cgroup_used_memory_without_cache) && !cg->memory.filename_detailed && (cgroup_used_memory_without_cache || cgroup_enable_systemd_services_detailed_memory || !(cg->options & CGROUP_OPTIONS_SYSTEM_SLICE_SERVICE)))) {
                snprintfz(filename, FILENAME_MAX, "%s%s/memory.stat", cgroup_unified_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->memory.filename_detailed = strdupz(filename);
                    cg->memory.enabled_detailed = (cgroup_enable_detailed_memory == CONFIG_BOOLEAN_YES)?CONFIG_BOOLEAN_YES:CONFIG_BOOLEAN_AUTO;
                    debug(D_CGROUP, "memory.stat filename for cgroup '%s': '%s'", cg->id, cg->memory.filename_detailed);
                }
                else
                    debug(D_CGROUP, "memory.stat file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_memory && !cg->memory.filename_usage_in_bytes)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/memory.current", cgroup_unified_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->memory.filename_usage_in_bytes = strdupz(filename);
                    cg->memory.enabled_usage_in_bytes = cgroup_enable_memory;
                    debug(D_CGROUP, "memory.current filename for cgroup '%s': '%s'", cg->id, cg->memory.filename_usage_in_bytes);
                    snprintfz(filename, FILENAME_MAX, "%s%s/memory.max", cgroup_unified_base, cg->id);
                    cg->filename_memory_limit = strdupz(filename);
                }
                else
                    debug(D_CGROUP, "memory.current file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }

            if(unlikely(cgroup_enable_swap && !cg->memory.filename_msw_usage_in_bytes)) {
                snprintfz(filename, FILENAME_MAX, "%s%s/memory.swap.current", cgroup_unified_base, cg->id);
                if(likely(stat(filename, &buf) != -1)) {
                    cg->memory.filename_msw_usage_in_bytes = strdupz(filename);
                    cg->memory.enabled_msw_usage_in_bytes = cgroup_enable_swap;
                    snprintfz(filename, FILENAME_MAX, "%s%s/memory.swap.max", cgroup_unified_base, cg->id);
                    cg->filename_memoryswap_limit = strdupz(filename);
                    debug(D_CGROUP, "memory.swap.current filename for cgroup '%s': '%s'", cg->id, cg->memory.filename_msw_usage_in_bytes);
                }
                else
                    debug(D_CGROUP, "memory.swap file for cgroup '%s': '%s' does not exist.", cg->id, filename);
            }
        }
    }

    debug(D_CGROUP, "done searching for cgroups");
}