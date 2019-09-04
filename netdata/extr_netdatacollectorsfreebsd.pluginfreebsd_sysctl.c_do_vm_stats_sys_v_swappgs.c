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
struct TYPE_2__ {int /*<<< orphan*/  v_swappgsout; int /*<<< orphan*/  v_swappgsin; } ;
typedef  TYPE_1__ vmmeter_t ;
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 scalar_t__ GETSYSCTL_SIMPLE (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KILO_FACTOR ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_SWAPIO ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_pagesize ; 
 scalar_t__ unlikely (int) ; 

int do_vm_stats_sys_v_swappgs(int update_every, usec_t dt) {
    (void)dt;
    static int mib_swappgsin[4] = {0, 0, 0, 0}, mib_swappgsout[4] = {0, 0, 0, 0};
    vmmeter_t vmmeter_data;

    if (unlikely(GETSYSCTL_SIMPLE("vm.stats.vm.v_swappgsin", mib_swappgsin, vmmeter_data.v_swappgsin) ||
                 GETSYSCTL_SIMPLE("vm.stats.vm.v_swappgsout", mib_swappgsout, vmmeter_data.v_swappgsout))) {
        error("DISABLED: system.swapio chart");
        error("DISABLED: vm.stats.vm.v_swappgs module");
        return 1;
    } else {

        // --------------------------------------------------------------------

        static RRDSET *st = NULL;
        static RRDDIM *rd_in = NULL, *rd_out = NULL;

        if (unlikely(!st)) {
            st = rrdset_create_localhost(
                    "system",
                    "swapio",
                    NULL,
                    "swap",
                    NULL,
                    "Swap I/O",
                    "KiB/s",
                    "freebsd.plugin",
                    "vm.stats.vm.v_swappgs",
                    NETDATA_CHART_PRIO_SYSTEM_SWAPIO,
                    update_every,
                    RRDSET_TYPE_AREA
            );

            rd_in = rrddim_add(st, "in",  NULL, system_pagesize, KILO_FACTOR, RRD_ALGORITHM_INCREMENTAL);
            rd_out = rrddim_add(st, "out", NULL, -system_pagesize, KILO_FACTOR, RRD_ALGORITHM_INCREMENTAL);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd_in, vmmeter_data.v_swappgsin);
        rrddim_set_by_pointer(st, rd_out, vmmeter_data.v_swappgsout);
        rrdset_done(st);
    }

    return 0;
}