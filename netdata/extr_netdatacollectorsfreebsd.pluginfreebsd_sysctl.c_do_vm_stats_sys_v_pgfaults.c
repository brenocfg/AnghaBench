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
struct TYPE_2__ {int /*<<< orphan*/  v_intrans; int /*<<< orphan*/  v_cow_optim; int /*<<< orphan*/  v_cow_faults; int /*<<< orphan*/  v_io_faults; int /*<<< orphan*/  v_vm_faults; } ;
typedef  TYPE_1__ vmmeter_t ;
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 scalar_t__ GETSYSCTL_SIMPLE (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_MEM_SYSTEM_PGFAULTS ; 
 int /*<<< orphan*/  RRDSET_FLAG_DETAIL ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_flag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_vm_stats_sys_v_pgfaults(int update_every, usec_t dt) {
    (void)dt;
    static int mib_vm_faults[4] = {0, 0, 0, 0}, mib_io_faults[4] = {0, 0, 0, 0}, mib_cow_faults[4] = {0, 0, 0, 0},
               mib_cow_optim[4] = {0, 0, 0, 0}, mib_intrans[4] = {0, 0, 0, 0};
    vmmeter_t vmmeter_data;

    if (unlikely(GETSYSCTL_SIMPLE("vm.stats.vm.v_vm_faults",  mib_vm_faults,  vmmeter_data.v_vm_faults) ||
                 GETSYSCTL_SIMPLE("vm.stats.vm.v_io_faults",  mib_io_faults,  vmmeter_data.v_io_faults) ||
                 GETSYSCTL_SIMPLE("vm.stats.vm.v_cow_faults", mib_cow_faults, vmmeter_data.v_cow_faults) ||
                 GETSYSCTL_SIMPLE("vm.stats.vm.v_cow_optim",  mib_cow_optim,  vmmeter_data.v_cow_optim) ||
                 GETSYSCTL_SIMPLE("vm.stats.vm.v_intrans",    mib_intrans,    vmmeter_data.v_intrans))) {
        error("DISABLED: mem.pgfaults chart");
        error("DISABLED: vm.stats.vm.v_pgfaults module");
        return 1;
    } else {

        // --------------------------------------------------------------------

        static RRDSET *st = NULL;
        static RRDDIM *rd_memory = NULL, *rd_io_requiring = NULL, *rd_cow = NULL,
                      *rd_cow_optimized = NULL, *rd_in_transit = NULL;

        if (unlikely(!st)) {
            st = rrdset_create_localhost(
                    "mem",
                    "pgfaults",
                    NULL,
                    "system",
                    NULL,
                    "Memory Page Faults",
                    "page faults/s",
                    "freebsd.plugin",
                    "vm.stats.vm.v_pgfaults",
                    NETDATA_CHART_PRIO_MEM_SYSTEM_PGFAULTS,
                    update_every,
                    RRDSET_TYPE_LINE
            );

            rrdset_flag_set(st, RRDSET_FLAG_DETAIL);

            rd_memory        = rrddim_add(st, "memory",        NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
            rd_io_requiring  = rrddim_add(st, "io_requiring",  NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
            rd_cow           = rrddim_add(st, "cow",           NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
            rd_cow_optimized = rrddim_add(st, "cow_optimized", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
            rd_in_transit    = rrddim_add(st, "in_transit",    NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_memory,        vmmeter_data.v_vm_faults);
        rrddim_set_by_pointer(st, rd_io_requiring,  vmmeter_data.v_io_faults);
        rrddim_set_by_pointer(st, rd_cow,           vmmeter_data.v_cow_faults);
        rrddim_set_by_pointer(st, rd_cow_optimized, vmmeter_data.v_cow_optim);
        rrddim_set_by_pointer(st, rd_in_transit,    vmmeter_data.v_intrans);
        rrdset_done(st);
    }

    return 0;
}