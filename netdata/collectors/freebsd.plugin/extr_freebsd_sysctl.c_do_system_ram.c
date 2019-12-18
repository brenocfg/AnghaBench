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
struct TYPE_2__ {int v_active_count; int v_inactive_count; int v_wire_count; int v_cache_count; int v_laundry_count; int v_free_count; } ;
typedef  TYPE_1__ vmmeter_t ;
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 scalar_t__ GETSYSCTL_SIMPLE (char*,int*,int) ; 
 int /*<<< orphan*/  MEGA_FACTOR ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_RAM ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int system_pagesize ; 
 scalar_t__ unlikely (int) ; 

int do_system_ram(int update_every, usec_t dt) {
    (void)dt;
    static int mib_active_count[4] = {0, 0, 0, 0}, mib_inactive_count[4] = {0, 0, 0, 0}, mib_wire_count[4] = {0, 0, 0, 0},
               mib_cache_count[4] = {0, 0, 0, 0}, mib_vfs_bufspace[2] = {0, 0}, mib_free_count[4] = {0, 0, 0, 0};
    vmmeter_t vmmeter_data;
    int vfs_bufspace_count;

#if defined(NETDATA_COLLECT_LAUNDRY)
    static int mib_laundry_count[4] = {0, 0, 0, 0};
#endif

    if (unlikely(GETSYSCTL_SIMPLE("vm.stats.vm.v_active_count",   mib_active_count,   vmmeter_data.v_active_count) ||
                 GETSYSCTL_SIMPLE("vm.stats.vm.v_inactive_count", mib_inactive_count, vmmeter_data.v_inactive_count) ||
                 GETSYSCTL_SIMPLE("vm.stats.vm.v_wire_count",     mib_wire_count,     vmmeter_data.v_wire_count) ||
#if __FreeBSD_version < 1200016
                 GETSYSCTL_SIMPLE("vm.stats.vm.v_cache_count",    mib_cache_count,    vmmeter_data.v_cache_count) ||
#endif
#if defined(NETDATA_COLLECT_LAUNDRY)
                 GETSYSCTL_SIMPLE("vm.stats.vm.v_laundry_count",  mib_laundry_count,  vmmeter_data.v_laundry_count) ||
#endif
                 GETSYSCTL_SIMPLE("vfs.bufspace",                 mib_vfs_bufspace,     vfs_bufspace_count) ||
                 GETSYSCTL_SIMPLE("vm.stats.vm.v_free_count",     mib_free_count,     vmmeter_data.v_free_count))) {
        error("DISABLED: system.ram chart");
        error("DISABLED: system.ram module");
        return 1;
    } else {

        // --------------------------------------------------------------------

        static RRDSET *st = NULL;
        static RRDDIM *rd_free = NULL, *rd_active = NULL, *rd_inactive = NULL, *rd_wired = NULL,
                      *rd_cache = NULL, *rd_buffers = NULL;

#if defined(NETDATA_COLLECT_LAUNDRY)
        static RRDDIM *rd_laundry = NULL;
#endif

        if (unlikely(!st)) {
            st = rrdset_create_localhost(
                    "system",
                    "ram",
                    NULL,
                    "ram",
                    NULL,
                    "System RAM",
                    "MiB",
                    "freebsd.plugin",
                    "system.ram",
                    NETDATA_CHART_PRIO_SYSTEM_RAM,
                    update_every,
                    RRDSET_TYPE_STACKED
            );

            rd_free     = rrddim_add(st, "free",     NULL, system_pagesize, MEGA_FACTOR, RRD_ALGORITHM_ABSOLUTE);
            rd_active   = rrddim_add(st, "active",   NULL, system_pagesize, MEGA_FACTOR, RRD_ALGORITHM_ABSOLUTE);
            rd_inactive = rrddim_add(st, "inactive", NULL, system_pagesize, MEGA_FACTOR, RRD_ALGORITHM_ABSOLUTE);
            rd_wired    = rrddim_add(st, "wired",    NULL, system_pagesize, MEGA_FACTOR, RRD_ALGORITHM_ABSOLUTE);
#if __FreeBSD_version < 1200016
            rd_cache    = rrddim_add(st, "cache",    NULL, system_pagesize, MEGA_FACTOR, RRD_ALGORITHM_ABSOLUTE);
#endif
#if defined(NETDATA_COLLECT_LAUNDRY)
            rd_laundry  = rrddim_add(st, "laundry",  NULL, system_pagesize, MEGA_FACTOR, RRD_ALGORITHM_ABSOLUTE);
#endif
            rd_buffers  = rrddim_add(st, "buffers",  NULL, 1, MEGA_FACTOR, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_free,     vmmeter_data.v_free_count);
        rrddim_set_by_pointer(st, rd_active,   vmmeter_data.v_active_count);
        rrddim_set_by_pointer(st, rd_inactive, vmmeter_data.v_inactive_count);
        rrddim_set_by_pointer(st, rd_wired,    vmmeter_data.v_wire_count);
#if __FreeBSD_version < 1200016
        rrddim_set_by_pointer(st, rd_cache,    vmmeter_data.v_cache_count);
#endif
#if defined(NETDATA_COLLECT_LAUNDRY)
        rrddim_set_by_pointer(st, rd_laundry,  vmmeter_data.v_laundry_count);
#endif
        rrddim_set_by_pointer(st, rd_buffers,  vfs_bufspace_count);
        rrdset_done(st);
    }

    return 0;
}