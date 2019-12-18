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
struct TYPE_2__ {scalar_t__ purges; scalar_t__ reactivations; scalar_t__ zero_fill_count; scalar_t__ decompressions; scalar_t__ compressions; scalar_t__ pageouts; scalar_t__ pageins; scalar_t__ cow_faults; scalar_t__ faults; scalar_t__ swapouts; scalar_t__ swapins; scalar_t__ speculative_count; scalar_t__ free_count; scalar_t__ purgeable_count; scalar_t__ inactive_count; scalar_t__ compressor_page_count; scalar_t__ throttled_count; scalar_t__ wire_count; scalar_t__ active_count; } ;
typedef  TYPE_1__ vm_statistics_data_t ;
typedef  int /*<<< orphan*/  vm_statistics64_data_t ;
typedef  int vm_size_t ;
typedef  int /*<<< orphan*/  usec_t ;
typedef  scalar_t__ natural_t ;
typedef  int mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  host_t ;
typedef  int /*<<< orphan*/  host_info_t ;
typedef  int /*<<< orphan*/  host_info64_t ;
typedef  int /*<<< orphan*/  RRDSET ;

/* Variables and functions */
 size_t CPU_STATE_IDLE ; 
 int CPU_STATE_MAX ; 
 size_t CPU_STATE_NICE ; 
 size_t CPU_STATE_SYSTEM ; 
 size_t CPU_STATE_USER ; 
 int /*<<< orphan*/  HOST_CPU_LOAD_INFO ; 
 int HOST_CPU_LOAD_INFO_COUNT ; 
 int /*<<< orphan*/  HOST_VM_INFO ; 
 int /*<<< orphan*/  HOST_VM_INFO64 ; 
 scalar_t__ KERN_SUCCESS ; 
 int NETDATA_CHART_PRIO_MEM_SYSTEM_PGFAULTS ; 
 int /*<<< orphan*/  RRDSET_FLAG_DETAIL ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL ; 
 int config_get_boolean (char*,char*,int) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ host_page_size (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ host_statistics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ host_statistics64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mach_error_string (scalar_t__) ; 
 int /*<<< orphan*/  mach_host_self () ; 
 int /*<<< orphan*/  rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_hide (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rrddim_set (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rrdset_find_bytype_localhost (char*,char*) ; 
 int /*<<< orphan*/ * rrdset_find_localhost (char*) ; 
 int /*<<< orphan*/  rrdset_flag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_macos_mach_smi(int update_every, usec_t dt) {
    (void)dt;

    static int do_cpu = -1, do_ram = - 1, do_swapio = -1, do_pgfaults = -1;

    if (unlikely(do_cpu == -1)) {
        do_cpu                  = config_get_boolean("plugin:macos:mach_smi", "cpu utilization", 1);
        do_ram                  = config_get_boolean("plugin:macos:mach_smi", "system ram", 1);
        do_swapio               = config_get_boolean("plugin:macos:mach_smi", "swap i/o", 1);
        do_pgfaults             = config_get_boolean("plugin:macos:mach_smi", "memory page faults", 1);
    }

    RRDSET *st;

	kern_return_t kr;
	mach_msg_type_number_t count;
    host_t host;
    vm_size_t system_pagesize;


    // NEEDED BY: do_cpu
    natural_t cp_time[CPU_STATE_MAX];

    // NEEDED BY: do_ram, do_swapio, do_pgfaults
#if (defined __MAC_OS_X_VERSION_MIN_REQUIRED && __MAC_OS_X_VERSION_MIN_REQUIRED >= 1060)
    vm_statistics64_data_t vm_statistics;
#else
    vm_statistics_data_t vm_statistics;
#endif

    host = mach_host_self();
    kr = host_page_size(host, &system_pagesize);
    if (unlikely(kr != KERN_SUCCESS))
        return -1;

    // --------------------------------------------------------------------

    if (likely(do_cpu)) {
        if (unlikely(HOST_CPU_LOAD_INFO_COUNT != 4)) {
            error("MACOS: There are %d CPU states (4 was expected)", HOST_CPU_LOAD_INFO_COUNT);
            do_cpu = 0;
            error("DISABLED: system.cpu");
        } else {
            count = HOST_CPU_LOAD_INFO_COUNT;
            kr = host_statistics(host, HOST_CPU_LOAD_INFO, (host_info_t)cp_time, &count);
            if (unlikely(kr != KERN_SUCCESS)) {
                error("MACOS: host_statistics() failed: %s", mach_error_string(kr));
                do_cpu = 0;
                error("DISABLED: system.cpu");
            } else {

                st = rrdset_find_bytype_localhost("system", "cpu");
                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "system"
                            , "cpu"
                            , NULL
                            , "cpu"
                            , "system.cpu"
                            , "Total CPU utilization"
                            , "percentage"
                            , "macos"
                            , "mach_smi"
                            , 100
                            , update_every
                            , RRDSET_TYPE_STACKED
                    );

                    rrddim_add(st, "user", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    rrddim_add(st, "nice", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    rrddim_add(st, "system", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    rrddim_add(st, "idle", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                    rrddim_hide(st, "idle");
                }
                else rrdset_next(st);

                rrddim_set(st, "user", cp_time[CPU_STATE_USER]);
                rrddim_set(st, "nice", cp_time[CPU_STATE_NICE]);
                rrddim_set(st, "system", cp_time[CPU_STATE_SYSTEM]);
                rrddim_set(st, "idle", cp_time[CPU_STATE_IDLE]);
                rrdset_done(st);
            }
        }
     }

    // --------------------------------------------------------------------

    if (likely(do_ram || do_swapio || do_pgfaults)) {
#if (defined __MAC_OS_X_VERSION_MIN_REQUIRED && __MAC_OS_X_VERSION_MIN_REQUIRED >= 1060)
        count = sizeof(vm_statistics64_data_t);
        kr = host_statistics64(host, HOST_VM_INFO64, (host_info64_t)&vm_statistics, &count);
#else
        count = sizeof(vm_statistics_data_t);
        kr = host_statistics(host, HOST_VM_INFO, (host_info_t)&vm_statistics, &count);
#endif
        if (unlikely(kr != KERN_SUCCESS)) {
            error("MACOS: host_statistics64() failed: %s", mach_error_string(kr));
            do_ram = 0;
            error("DISABLED: system.ram");
            do_swapio = 0;
            error("DISABLED: system.swapio");
            do_pgfaults = 0;
            error("DISABLED: mem.pgfaults");
        } else {
            if (likely(do_ram)) {
                st = rrdset_find_localhost("system.ram");
                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "system"
                            , "ram"
                            , NULL
                            , "ram"
                            , NULL
                            , "System RAM"
                            , "MiB"
                            , "macos"
                            , "mach_smi"
                            , 200
                            , update_every
                            , RRDSET_TYPE_STACKED
                    );

                    rrddim_add(st, "active",    NULL, system_pagesize, 1048576, RRD_ALGORITHM_ABSOLUTE);
                    rrddim_add(st, "wired",     NULL, system_pagesize, 1048576, RRD_ALGORITHM_ABSOLUTE);
#if (defined __MAC_OS_X_VERSION_MIN_REQUIRED && __MAC_OS_X_VERSION_MIN_REQUIRED >= 1090)
                    rrddim_add(st, "throttled", NULL, system_pagesize, 1048576, RRD_ALGORITHM_ABSOLUTE);
                    rrddim_add(st, "compressor", NULL, system_pagesize, 1048576, RRD_ALGORITHM_ABSOLUTE);
#endif
                    rrddim_add(st, "inactive",  NULL, system_pagesize, 1048576, RRD_ALGORITHM_ABSOLUTE);
                    rrddim_add(st, "purgeable", NULL, system_pagesize, 1048576, RRD_ALGORITHM_ABSOLUTE);
                    rrddim_add(st, "speculative", NULL, system_pagesize, 1048576, RRD_ALGORITHM_ABSOLUTE);
                    rrddim_add(st, "free",      NULL, system_pagesize, 1048576, RRD_ALGORITHM_ABSOLUTE);
                }
                else rrdset_next(st);

                rrddim_set(st, "active",    vm_statistics.active_count);
                rrddim_set(st, "wired",     vm_statistics.wire_count);
#if (defined __MAC_OS_X_VERSION_MIN_REQUIRED && __MAC_OS_X_VERSION_MIN_REQUIRED >= 1090)
                rrddim_set(st, "throttled", vm_statistics.throttled_count);
                rrddim_set(st, "compressor", vm_statistics.compressor_page_count);
#endif
                rrddim_set(st, "inactive",  vm_statistics.inactive_count);
                rrddim_set(st, "purgeable", vm_statistics.purgeable_count);
                rrddim_set(st, "speculative", vm_statistics.speculative_count);
                rrddim_set(st, "free",      (vm_statistics.free_count - vm_statistics.speculative_count));
                rrdset_done(st);
            }

#if (defined __MAC_OS_X_VERSION_MIN_REQUIRED && __MAC_OS_X_VERSION_MIN_REQUIRED >= 1090)
            // --------------------------------------------------------------------

            if (likely(do_swapio)) {
                st = rrdset_find_localhost("system.swapio");
                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "system"
                            , "swapio"
                            , NULL
                            , "swap"
                            , NULL
                            , "Swap I/O"
                            , "KiB/s"
                            , "macos"
                            , "mach_smi"
                            , 250
                            , update_every
                            , RRDSET_TYPE_AREA
                    );

                    rrddim_add(st, "in",  NULL, system_pagesize, 1024, RRD_ALGORITHM_INCREMENTAL);
                    rrddim_add(st, "out", NULL, -system_pagesize, 1024, RRD_ALGORITHM_INCREMENTAL);
                }
                else rrdset_next(st);

                rrddim_set(st, "in", vm_statistics.swapins);
                rrddim_set(st, "out", vm_statistics.swapouts);
                rrdset_done(st);
            }
#endif

            // --------------------------------------------------------------------

            if (likely(do_pgfaults)) {
                st = rrdset_find_localhost("mem.pgfaults");
                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "mem"
                            , "pgfaults"
                            , NULL
                            , "system"
                            , NULL
                            , "Memory Page Faults"
                            , "faults/s"
                            , "macos"
                            , "mach_smi"
                            , NETDATA_CHART_PRIO_MEM_SYSTEM_PGFAULTS
                            , update_every
                            , RRDSET_TYPE_LINE
                    );
                    rrdset_flag_set(st, RRDSET_FLAG_DETAIL);

                    rrddim_add(st, "memory",    NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rrddim_add(st, "cow",       NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rrddim_add(st, "pagein",    NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rrddim_add(st, "pageout",   NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
#if (defined __MAC_OS_X_VERSION_MIN_REQUIRED && __MAC_OS_X_VERSION_MIN_REQUIRED >= 1090)
                    rrddim_add(st, "compress",  NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rrddim_add(st, "decompress", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
#endif
                    rrddim_add(st, "zero_fill", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rrddim_add(st, "reactivate", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
                    rrddim_add(st, "purge",     NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
                }
                else rrdset_next(st);

                rrddim_set(st, "memory", vm_statistics.faults);
                rrddim_set(st, "cow", vm_statistics.cow_faults);
                rrddim_set(st, "pagein", vm_statistics.pageins);
                rrddim_set(st, "pageout", vm_statistics.pageouts);
#if (defined __MAC_OS_X_VERSION_MIN_REQUIRED && __MAC_OS_X_VERSION_MIN_REQUIRED >= 1090)
                rrddim_set(st, "compress", vm_statistics.compressions);
                rrddim_set(st, "decompress", vm_statistics.decompressions);
#endif
                rrddim_set(st, "zero_fill", vm_statistics.zero_fill_count);
                rrddim_set(st, "reactivate", vm_statistics.reactivations);
                rrddim_set(st, "purge", vm_statistics.purges);
                rrdset_done(st);
            }
        }
    }

    // --------------------------------------------------------------------

    return 0;
}