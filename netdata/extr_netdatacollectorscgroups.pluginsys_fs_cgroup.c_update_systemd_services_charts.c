#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ Write; scalar_t__ Read; scalar_t__ updated; } ;
struct TYPE_15__ {scalar_t__ Write; scalar_t__ Read; scalar_t__ updated; } ;
struct TYPE_14__ {scalar_t__ Write; scalar_t__ Read; scalar_t__ updated; } ;
struct TYPE_13__ {scalar_t__ Write; scalar_t__ Read; scalar_t__ updated; } ;
struct TYPE_12__ {scalar_t__ Write; scalar_t__ Read; scalar_t__ updated; } ;
struct TYPE_11__ {scalar_t__ Write; scalar_t__ Read; scalar_t__ updated; } ;
struct TYPE_10__ {scalar_t__ msw_usage_in_bytes; scalar_t__ updated_msw_usage_in_bytes; scalar_t__ failcnt; scalar_t__ updated_failcnt; scalar_t__ total_pgpgout; scalar_t__ total_pgpgin; scalar_t__ total_pgmajfault; scalar_t__ total_pgfault; scalar_t__ total_writeback; scalar_t__ total_cache; scalar_t__ total_mapped_file; scalar_t__ total_rss_huge; scalar_t__ total_rss; scalar_t__ updated_detailed; scalar_t__ usage_in_bytes; scalar_t__ updated_usage_in_bytes; } ;
struct TYPE_9__ {scalar_t__ system; scalar_t__ user; scalar_t__ updated; } ;
struct cgroup {int options; TYPE_8__ io_merged; void* rd_io_merged_write; int /*<<< orphan*/  chart_title; int /*<<< orphan*/  chart_id; void* rd_io_merged_read; TYPE_7__ io_queued; void* rd_io_queued_write; void* rd_io_queued_read; TYPE_6__ throttle_io_serviced; void* rd_throttle_io_serviced_write; void* rd_throttle_io_serviced_read; TYPE_5__ throttle_io_service_bytes; void* rd_throttle_io_write; void* rd_throttle_io_read; TYPE_4__ io_serviced; void* rd_io_serviced_write; void* rd_io_serviced_read; TYPE_3__ io_service_bytes; void* rd_io_service_bytes_write; void* rd_io_service_bytes_read; TYPE_2__ memory; void* rd_swap_usage; void* rd_mem_failcnt; void* rd_mem_detailed_pgpgout; void* rd_mem_detailed_pgpgin; void* rd_mem_detailed_pgmajfault; void* rd_mem_detailed_pgfault; void* rd_mem_detailed_writeback; void* rd_mem_detailed_cache; void* rd_mem_detailed_mapped; void* rd_mem_detailed_rss; void* rd_mem_usage; TYPE_1__ cpuacct_stat; void* rd_cpu; scalar_t__ pending_renames; int /*<<< orphan*/  enabled; int /*<<< orphan*/  available; struct cgroup* next; } ;
typedef  int /*<<< orphan*/  RRDSET ;

/* Variables and functions */
 int CGROUP_OPTIONS_IS_UNIFIED ; 
 int CGROUP_OPTIONS_SYSTEM_SLICE_SERVICE ; 
 int /*<<< orphan*/  CHART_TITLE_MAX ; 
 scalar_t__ NETDATA_CHART_PRIO_CGROUPS_SYSTEMD ; 
 int /*<<< orphan*/  PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME ; 
 int /*<<< orphan*/  PLUGIN_CGROUPS_NAME ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 struct cgroup* cgroup_root ; 
 scalar_t__ cgroup_used_memory_without_cache ; 
 scalar_t__ likely (int) ; 
 int processors ; 
 void* rrddim_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int,int,char*) ; 
 int system_hz ; 
 int system_page_size ; 
 scalar_t__ unlikely (int) ; 

void update_systemd_services_charts(
          int update_every
        , int do_cpu
        , int do_mem_usage
        , int do_mem_detailed
        , int do_mem_failcnt
        , int do_swap_usage
        , int do_io
        , int do_io_ops
        , int do_throttle_io
        , int do_throttle_ops
        , int do_queued_ops
        , int do_merged_ops
) {
    static RRDSET
        *st_cpu = NULL,
        *st_mem_usage = NULL,
        *st_mem_failcnt = NULL,
        *st_swap_usage = NULL,

        *st_mem_detailed_cache = NULL,
        *st_mem_detailed_rss = NULL,
        *st_mem_detailed_mapped = NULL,
        *st_mem_detailed_writeback = NULL,
        *st_mem_detailed_pgfault = NULL,
        *st_mem_detailed_pgmajfault = NULL,
        *st_mem_detailed_pgpgin = NULL,
        *st_mem_detailed_pgpgout = NULL,

        *st_io_read = NULL,
        *st_io_serviced_read = NULL,
        *st_throttle_io_read = NULL,
        *st_throttle_ops_read = NULL,
        *st_queued_ops_read = NULL,
        *st_merged_ops_read = NULL,

        *st_io_write = NULL,
        *st_io_serviced_write = NULL,
        *st_throttle_io_write = NULL,
        *st_throttle_ops_write = NULL,
        *st_queued_ops_write = NULL,
        *st_merged_ops_write = NULL;

    // create the charts

    if(likely(do_cpu)) {
        if(unlikely(!st_cpu)) {
            char title[CHART_TITLE_MAX + 1];
            snprintfz(title, CHART_TITLE_MAX, "Systemd Services CPU utilization (%d%% = %d core%s)", (processors * 100), processors, (processors > 1) ? "s" : "");

            st_cpu = rrdset_create_localhost(
                    "services"
                    , "cpu"
                    , NULL
                    , "cpu"
                    , "services.cpu"
                    , title
                    , "percentage"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_cpu);
    }

    if(likely(do_mem_usage)) {
        if(unlikely(!st_mem_usage)) {

            st_mem_usage = rrdset_create_localhost(
                    "services"
                    , "mem_usage"
                    , NULL
                    , "mem"
                    , "services.mem_usage"
                    , (cgroup_used_memory_without_cache) ? "Systemd Services Used Memory without Cache"
                                                         : "Systemd Services Used Memory"
                    , "MiB"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 10
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_mem_usage);
    }

    if(likely(do_mem_detailed)) {
        if(unlikely(!st_mem_detailed_rss)) {

            st_mem_detailed_rss = rrdset_create_localhost(
                    "services"
                    , "mem_rss"
                    , NULL
                    , "mem"
                    , "services.mem_rss"
                    , "Systemd Services RSS Memory"
                    , "MiB"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 20
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_mem_detailed_rss);

        if(unlikely(!st_mem_detailed_mapped)) {

            st_mem_detailed_mapped = rrdset_create_localhost(
                    "services"
                    , "mem_mapped"
                    , NULL
                    , "mem"
                    , "services.mem_mapped"
                    , "Systemd Services Mapped Memory"
                    , "MiB"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 30
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_mem_detailed_mapped);

        if(unlikely(!st_mem_detailed_cache)) {

            st_mem_detailed_cache = rrdset_create_localhost(
                    "services"
                    , "mem_cache"
                    , NULL
                    , "mem"
                    , "services.mem_cache"
                    , "Systemd Services Cache Memory"
                    , "MiB"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 40
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_mem_detailed_cache);

        if(unlikely(!st_mem_detailed_writeback)) {

            st_mem_detailed_writeback = rrdset_create_localhost(
                    "services"
                    , "mem_writeback"
                    , NULL
                    , "mem"
                    , "services.mem_writeback"
                    , "Systemd Services Writeback Memory"
                    , "MiB"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 50
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_mem_detailed_writeback);

        if(unlikely(!st_mem_detailed_pgfault)) {

            st_mem_detailed_pgfault = rrdset_create_localhost(
                    "services"
                    , "mem_pgfault"
                    , NULL
                    , "mem"
                    , "services.mem_pgfault"
                    , "Systemd Services Memory Minor Page Faults"
                    , "MiB/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 60
                    , update_every
                    , RRDSET_TYPE_STACKED
            );
        }
        else
            rrdset_next(st_mem_detailed_pgfault);

        if(unlikely(!st_mem_detailed_pgmajfault)) {

            st_mem_detailed_pgmajfault = rrdset_create_localhost(
                    "services"
                    , "mem_pgmajfault"
                    , NULL
                    , "mem"
                    , "services.mem_pgmajfault"
                    , "Systemd Services Memory Major Page Faults"
                    , "MiB/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 70
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_mem_detailed_pgmajfault);

        if(unlikely(!st_mem_detailed_pgpgin)) {

            st_mem_detailed_pgpgin = rrdset_create_localhost(
                    "services"
                    , "mem_pgpgin"
                    , NULL
                    , "mem"
                    , "services.mem_pgpgin"
                    , "Systemd Services Memory Charging Activity"
                    , "MiB/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 80
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_mem_detailed_pgpgin);

        if(unlikely(!st_mem_detailed_pgpgout)) {

            st_mem_detailed_pgpgout = rrdset_create_localhost(
                    "services"
                    , "mem_pgpgout"
                    , NULL
                    , "mem"
                    , "services.mem_pgpgout"
                    , "Systemd Services Memory Uncharging Activity"
                    , "MiB/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 90
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_mem_detailed_pgpgout);
    }

    if(likely(do_mem_failcnt)) {
        if(unlikely(!st_mem_failcnt)) {

            st_mem_failcnt = rrdset_create_localhost(
                    "services"
                    , "mem_failcnt"
                    , NULL
                    , "mem"
                    , "services.mem_failcnt"
                    , "Systemd Services Memory Limit Failures"
                    , "failures"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 110
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_mem_failcnt);
    }

    if(likely(do_swap_usage)) {
        if(unlikely(!st_swap_usage)) {

            st_swap_usage = rrdset_create_localhost(
                    "services"
                    , "swap_usage"
                    , NULL
                    , "swap"
                    , "services.swap_usage"
                    , "Systemd Services Swap Memory Used"
                    , "MiB"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 100
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_swap_usage);
    }

    if(likely(do_io)) {
        if(unlikely(!st_io_read)) {

            st_io_read = rrdset_create_localhost(
                    "services"
                    , "io_read"
                    , NULL
                    , "disk"
                    , "services.io_read"
                    , "Systemd Services Disk Read Bandwidth"
                    , "KiB/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 120
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_io_read);

        if(unlikely(!st_io_write)) {

            st_io_write = rrdset_create_localhost(
                    "services"
                    , "io_write"
                    , NULL
                    , "disk"
                    , "services.io_write"
                    , "Systemd Services Disk Write Bandwidth"
                    , "KiB/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 130
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_io_write);
    }

    if(likely(do_io_ops)) {
        if(unlikely(!st_io_serviced_read)) {

            st_io_serviced_read = rrdset_create_localhost(
                    "services"
                    , "io_ops_read"
                    , NULL
                    , "disk"
                    , "services.io_ops_read"
                    , "Systemd Services Disk Read Operations"
                    , "operations/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 140
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_io_serviced_read);

        if(unlikely(!st_io_serviced_write)) {

            st_io_serviced_write = rrdset_create_localhost(
                    "services"
                    , "io_ops_write"
                    , NULL
                    , "disk"
                    , "services.io_ops_write"
                    , "Systemd Services Disk Write Operations"
                    , "operations/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 150
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_io_serviced_write);
    }

    if(likely(do_throttle_io)) {
        if(unlikely(!st_throttle_io_read)) {

            st_throttle_io_read = rrdset_create_localhost(
                    "services"
                    , "throttle_io_read"
                    , NULL
                    , "disk"
                    , "services.throttle_io_read"
                    , "Systemd Services Throttle Disk Read Bandwidth"
                    , "KiB/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 160
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_throttle_io_read);

        if(unlikely(!st_throttle_io_write)) {

            st_throttle_io_write = rrdset_create_localhost(
                    "services"
                    , "throttle_io_write"
                    , NULL
                    , "disk"
                    , "services.throttle_io_write"
                    , "Systemd Services Throttle Disk Write Bandwidth"
                    , "KiB/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 170
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_throttle_io_write);
    }

    if(likely(do_throttle_ops)) {
        if(unlikely(!st_throttle_ops_read)) {

            st_throttle_ops_read = rrdset_create_localhost(
                    "services"
                    , "throttle_io_ops_read"
                    , NULL
                    , "disk"
                    , "services.throttle_io_ops_read"
                    , "Systemd Services Throttle Disk Read Operations"
                    , "operations/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 180
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_throttle_ops_read);

        if(unlikely(!st_throttle_ops_write)) {

            st_throttle_ops_write = rrdset_create_localhost(
                    "services"
                    , "throttle_io_ops_write"
                    , NULL
                    , "disk"
                    , "services.throttle_io_ops_write"
                    , "Systemd Services Throttle Disk Write Operations"
                    , "operations/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 190
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_throttle_ops_write);
    }

    if(likely(do_queued_ops)) {
        if(unlikely(!st_queued_ops_read)) {

            st_queued_ops_read = rrdset_create_localhost(
                    "services"
                    , "queued_io_ops_read"
                    , NULL
                    , "disk"
                    , "services.queued_io_ops_read"
                    , "Systemd Services Queued Disk Read Operations"
                    , "operations/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 200
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_queued_ops_read);

        if(unlikely(!st_queued_ops_write)) {

            st_queued_ops_write = rrdset_create_localhost(
                    "services"
                    , "queued_io_ops_write"
                    , NULL
                    , "disk"
                    , "services.queued_io_ops_write"
                    , "Systemd Services Queued Disk Write Operations"
                    , "operations/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 210
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_queued_ops_write);
    }

    if(likely(do_merged_ops)) {
        if(unlikely(!st_merged_ops_read)) {

            st_merged_ops_read = rrdset_create_localhost(
                    "services"
                    , "merged_io_ops_read"
                    , NULL
                    , "disk"
                    , "services.merged_io_ops_read"
                    , "Systemd Services Merged Disk Read Operations"
                    , "operations/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 220
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_merged_ops_read);

        if(unlikely(!st_merged_ops_write)) {

            st_merged_ops_write = rrdset_create_localhost(
                    "services"
                    , "merged_io_ops_write"
                    , NULL
                    , "disk"
                    , "services.merged_io_ops_write"
                    , "Systemd Services Merged Disk Write Operations"
                    , "operations/s"
                    , PLUGIN_CGROUPS_NAME
                    , PLUGIN_CGROUPS_MODULE_SYSTEMD_NAME
                    , NETDATA_CHART_PRIO_CGROUPS_SYSTEMD + 230
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

        }
        else
            rrdset_next(st_merged_ops_write);
    }

    // update the values
    struct cgroup *cg;
    for(cg = cgroup_root; cg ; cg = cg->next) {
        if(unlikely(!cg->available || !cg->enabled || cg->pending_renames || !(cg->options & CGROUP_OPTIONS_SYSTEM_SLICE_SERVICE)))
            continue;

        if(likely(do_cpu && cg->cpuacct_stat.updated)) {
            if(unlikely(!cg->rd_cpu)){


                if (!(cg->options & CGROUP_OPTIONS_IS_UNIFIED)) {
                    cg->rd_cpu = rrddim_add(st_cpu, cg->chart_id, cg->chart_title, 100, system_hz, RRD_ALGORITHM_INCREMENTAL);
                } else {
                    cg->rd_cpu = rrddim_add(st_cpu, cg->chart_id, cg->chart_title, 100, 1000000, RRD_ALGORITHM_INCREMENTAL);
                }
            }

            rrddim_set_by_pointer(st_cpu, cg->rd_cpu, cg->cpuacct_stat.user + cg->cpuacct_stat.system);
        }

        if(likely(do_mem_usage && cg->memory.updated_usage_in_bytes)) {
            if(unlikely(!cg->rd_mem_usage))
                cg->rd_mem_usage = rrddim_add(st_mem_usage, cg->chart_id, cg->chart_title, 1, 1024 * 1024, RRD_ALGORITHM_ABSOLUTE);

            rrddim_set_by_pointer(st_mem_usage, cg->rd_mem_usage, cg->memory.usage_in_bytes - ((cgroup_used_memory_without_cache)?cg->memory.total_cache:0));
        }

        if(likely(do_mem_detailed && cg->memory.updated_detailed)) {
            if(unlikely(!cg->rd_mem_detailed_rss))
                cg->rd_mem_detailed_rss = rrddim_add(st_mem_detailed_rss, cg->chart_id, cg->chart_title, 1, 1024 * 1024, RRD_ALGORITHM_ABSOLUTE);

            rrddim_set_by_pointer(st_mem_detailed_rss, cg->rd_mem_detailed_rss, cg->memory.total_rss + cg->memory.total_rss_huge);

            if(unlikely(!cg->rd_mem_detailed_mapped))
                cg->rd_mem_detailed_mapped = rrddim_add(st_mem_detailed_mapped, cg->chart_id, cg->chart_title, 1, 1024 * 1024, RRD_ALGORITHM_ABSOLUTE);

            rrddim_set_by_pointer(st_mem_detailed_mapped, cg->rd_mem_detailed_mapped, cg->memory.total_mapped_file);

            if(unlikely(!cg->rd_mem_detailed_cache))
                cg->rd_mem_detailed_cache = rrddim_add(st_mem_detailed_cache, cg->chart_id, cg->chart_title, 1, 1024 * 1024, RRD_ALGORITHM_ABSOLUTE);

            rrddim_set_by_pointer(st_mem_detailed_cache, cg->rd_mem_detailed_cache, cg->memory.total_cache);

            if(unlikely(!cg->rd_mem_detailed_writeback))
                cg->rd_mem_detailed_writeback = rrddim_add(st_mem_detailed_writeback, cg->chart_id, cg->chart_title, 1, 1024 * 1024, RRD_ALGORITHM_ABSOLUTE);

            rrddim_set_by_pointer(st_mem_detailed_writeback, cg->rd_mem_detailed_writeback, cg->memory.total_writeback);

            if(unlikely(!cg->rd_mem_detailed_pgfault))
                cg->rd_mem_detailed_pgfault = rrddim_add(st_mem_detailed_pgfault, cg->chart_id, cg->chart_title, system_page_size, 1024 * 1024, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_mem_detailed_pgfault, cg->rd_mem_detailed_pgfault, cg->memory.total_pgfault);

            if(unlikely(!cg->rd_mem_detailed_pgmajfault))
                cg->rd_mem_detailed_pgmajfault = rrddim_add(st_mem_detailed_pgmajfault, cg->chart_id, cg->chart_title, system_page_size, 1024 * 1024, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_mem_detailed_pgmajfault, cg->rd_mem_detailed_pgmajfault, cg->memory.total_pgmajfault);

            if(unlikely(!cg->rd_mem_detailed_pgpgin))
                cg->rd_mem_detailed_pgpgin = rrddim_add(st_mem_detailed_pgpgin, cg->chart_id, cg->chart_title, system_page_size, 1024 * 1024, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_mem_detailed_pgpgin, cg->rd_mem_detailed_pgpgin, cg->memory.total_pgpgin);

            if(unlikely(!cg->rd_mem_detailed_pgpgout))
                cg->rd_mem_detailed_pgpgout = rrddim_add(st_mem_detailed_pgpgout, cg->chart_id, cg->chart_title, system_page_size, 1024 * 1024, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_mem_detailed_pgpgout, cg->rd_mem_detailed_pgpgout, cg->memory.total_pgpgout);
        }

        if(likely(do_mem_failcnt && cg->memory.updated_failcnt)) {
            if(unlikely(!cg->rd_mem_failcnt))
                cg->rd_mem_failcnt = rrddim_add(st_mem_failcnt, cg->chart_id, cg->chart_title, 1, 1, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_mem_failcnt, cg->rd_mem_failcnt, cg->memory.failcnt);
        }

        if(likely(do_swap_usage && cg->memory.updated_msw_usage_in_bytes)) {
            if(unlikely(!cg->rd_swap_usage))
                cg->rd_swap_usage = rrddim_add(st_swap_usage, cg->chart_id, cg->chart_title, 1, 1024 * 1024, RRD_ALGORITHM_ABSOLUTE);

            rrddim_set_by_pointer(st_swap_usage, cg->rd_swap_usage, cg->memory.msw_usage_in_bytes);
        }

        if(likely(do_io && cg->io_service_bytes.updated)) {
            if(unlikely(!cg->rd_io_service_bytes_read))
                cg->rd_io_service_bytes_read = rrddim_add(st_io_read, cg->chart_id, cg->chart_title, 1, 1024, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_io_read, cg->rd_io_service_bytes_read, cg->io_service_bytes.Read);

            if(unlikely(!cg->rd_io_service_bytes_write))
                cg->rd_io_service_bytes_write = rrddim_add(st_io_write, cg->chart_id, cg->chart_title, 1, 1024, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_io_write, cg->rd_io_service_bytes_write, cg->io_service_bytes.Write);
        }

        if(likely(do_io_ops && cg->io_serviced.updated)) {
            if(unlikely(!cg->rd_io_serviced_read))
                cg->rd_io_serviced_read = rrddim_add(st_io_serviced_read, cg->chart_id, cg->chart_title, 1, 1, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_io_serviced_read, cg->rd_io_serviced_read, cg->io_serviced.Read);

            if(unlikely(!cg->rd_io_serviced_write))
                cg->rd_io_serviced_write = rrddim_add(st_io_serviced_write, cg->chart_id, cg->chart_title, 1, 1, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_io_serviced_write, cg->rd_io_serviced_write, cg->io_serviced.Write);
        }

        if(likely(do_throttle_io && cg->throttle_io_service_bytes.updated)) {
            if(unlikely(!cg->rd_throttle_io_read))
                cg->rd_throttle_io_read = rrddim_add(st_throttle_io_read, cg->chart_id, cg->chart_title, 1, 1024, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_throttle_io_read, cg->rd_throttle_io_read, cg->throttle_io_service_bytes.Read);

            if(unlikely(!cg->rd_throttle_io_write))
                cg->rd_throttle_io_write = rrddim_add(st_throttle_io_write, cg->chart_id, cg->chart_title, 1, 1024, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_throttle_io_write, cg->rd_throttle_io_write, cg->throttle_io_service_bytes.Write);
        }

        if(likely(do_throttle_ops && cg->throttle_io_serviced.updated)) {
            if(unlikely(!cg->rd_throttle_io_serviced_read))
                cg->rd_throttle_io_serviced_read = rrddim_add(st_throttle_ops_read, cg->chart_id, cg->chart_title, 1, 1, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_throttle_ops_read, cg->rd_throttle_io_serviced_read, cg->throttle_io_serviced.Read);

            if(unlikely(!cg->rd_throttle_io_serviced_write))
                cg->rd_throttle_io_serviced_write = rrddim_add(st_throttle_ops_write, cg->chart_id, cg->chart_title, 1, 1, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_throttle_ops_write, cg->rd_throttle_io_serviced_write, cg->throttle_io_serviced.Write);
        }

        if(likely(do_queued_ops && cg->io_queued.updated)) {
            if(unlikely(!cg->rd_io_queued_read))
                cg->rd_io_queued_read = rrddim_add(st_queued_ops_read, cg->chart_id, cg->chart_title, 1, 1, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_queued_ops_read, cg->rd_io_queued_read, cg->io_queued.Read);

            if(unlikely(!cg->rd_io_queued_write))
                cg->rd_io_queued_write = rrddim_add(st_queued_ops_write, cg->chart_id, cg->chart_title, 1, 1, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_queued_ops_write, cg->rd_io_queued_write, cg->io_queued.Write);
        }

        if(likely(do_merged_ops && cg->io_merged.updated)) {
            if(unlikely(!cg->rd_io_merged_read))
                cg->rd_io_merged_read = rrddim_add(st_merged_ops_read, cg->chart_id, cg->chart_title, 1, 1, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_merged_ops_read, cg->rd_io_merged_read, cg->io_merged.Read);

            if(unlikely(!cg->rd_io_merged_write))
                cg->rd_io_merged_write = rrddim_add(st_merged_ops_write, cg->chart_id, cg->chart_title, 1, 1, RRD_ALGORITHM_INCREMENTAL);

            rrddim_set_by_pointer(st_merged_ops_write, cg->rd_io_merged_write, cg->io_merged.Write);
        }
    }

    // complete the iteration
    if(likely(do_cpu))
        rrdset_done(st_cpu);

    if(likely(do_mem_usage))
        rrdset_done(st_mem_usage);

    if(unlikely(do_mem_detailed)) {
        rrdset_done(st_mem_detailed_cache);
        rrdset_done(st_mem_detailed_rss);
        rrdset_done(st_mem_detailed_mapped);
        rrdset_done(st_mem_detailed_writeback);
        rrdset_done(st_mem_detailed_pgfault);
        rrdset_done(st_mem_detailed_pgmajfault);
        rrdset_done(st_mem_detailed_pgpgin);
        rrdset_done(st_mem_detailed_pgpgout);
    }

    if(likely(do_mem_failcnt))
        rrdset_done(st_mem_failcnt);

    if(likely(do_swap_usage))
        rrdset_done(st_swap_usage);

    if(likely(do_io)) {
        rrdset_done(st_io_read);
        rrdset_done(st_io_write);
    }

    if(likely(do_io_ops)) {
        rrdset_done(st_io_serviced_read);
        rrdset_done(st_io_serviced_write);
    }

    if(likely(do_throttle_io)) {
        rrdset_done(st_throttle_io_read);
        rrdset_done(st_throttle_io_write);
    }

    if(likely(do_throttle_ops)) {
        rrdset_done(st_throttle_ops_read);
        rrdset_done(st_throttle_ops_write);
    }

    if(likely(do_queued_ops)) {
        rrdset_done(st_queued_ops_read);
        rrdset_done(st_queued_ops_write);
    }

    if(likely(do_merged_ops)) {
        rrdset_done(st_merged_ops_read);
        rrdset_done(st_merged_ops_write);
    }
}