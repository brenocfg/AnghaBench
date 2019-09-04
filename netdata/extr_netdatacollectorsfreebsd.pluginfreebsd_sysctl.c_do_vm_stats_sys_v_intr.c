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
typedef  int /*<<< orphan*/  usec_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int GETSYSCTL_SIMPLE (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_DEV_INTR ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_vm_stats_sys_v_intr(int update_every, usec_t dt) {
    (void)dt;
    static int mib[4] = {0, 0, 0, 0};
    u_int int_number;

    if (unlikely(GETSYSCTL_SIMPLE("vm.stats.sys.v_intr", mib, int_number))) {
        error("DISABLED: system.dev_intr chart");
        error("DISABLED: vm.stats.sys.v_intr module");
        return 1;
    } else {

        // --------------------------------------------------------------------

        static RRDSET *st = NULL;
        static RRDDIM *rd = NULL;

        if (unlikely(!st)) {
            st = rrdset_create_localhost(
                    "system",
                    "dev_intr",
                    NULL,
                    "interrupts",
                    NULL,
                    "Device Interrupts",
                    "interrupts/s",
                    "freebsd.plugin",
                    "vm.stats.sys.v_intr",
                    NETDATA_CHART_PRIO_SYSTEM_DEV_INTR,
                    update_every,
                    RRDSET_TYPE_LINE
            );

            rd = rrddim_add(st, "interrupts", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd, int_number);
        rrdset_done(st);
    }

    return 0;
}