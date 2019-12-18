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
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int CPUSTATES ; 
 int GETSYSCTL_SIMPLE (char*,int*,long*) ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_CPU ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_hide (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_kern_cp_time(int update_every, usec_t dt) {
    (void)dt;

    if (unlikely(CPUSTATES != 5)) {
        error("FREEBSD: There are %d CPU states (5 was expected)", CPUSTATES);
        error("DISABLED: system.cpu chart");
        error("DISABLED: kern.cp_time module");
        return 1;
    } else {
        static int mib[2] = {0, 0};
        long cp_time[CPUSTATES];

        if (unlikely(GETSYSCTL_SIMPLE("kern.cp_time", mib, cp_time))) {
            error("DISABLED: system.cpu chart");
            error("DISABLED: kern.cp_time module");
            return 1;
        } else {

            // --------------------------------------------------------------------

            static RRDSET *st = NULL;
            static RRDDIM *rd_nice = NULL, *rd_system = NULL, *rd_user = NULL, *rd_interrupt = NULL, *rd_idle = NULL;

            if (unlikely(!st)) {
                st = rrdset_create_localhost(
                        "system",
                        "cpu",
                        NULL,
                        "cpu",
                        "system.cpu",
                        "Total CPU utilization",
                        "percentage",
                        "freebsd.plugin",
                        "kern.cp_time",
                        NETDATA_CHART_PRIO_SYSTEM_CPU,
                        update_every,
                        RRDSET_TYPE_STACKED
                );

                rd_nice         = rrddim_add(st, "nice", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                rd_system       = rrddim_add(st, "system", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                rd_user         = rrddim_add(st, "user", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                rd_interrupt    = rrddim_add(st, "interrupt", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                rd_idle         = rrddim_add(st, "idle", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
                rrddim_hide(st, "idle");
            }
            else rrdset_next(st);

            rrddim_set_by_pointer(st, rd_nice, cp_time[1]);
            rrddim_set_by_pointer(st, rd_system, cp_time[2]);
            rrddim_set_by_pointer(st, rd_user, cp_time[0]);
            rrddim_set_by_pointer(st, rd_interrupt, cp_time[3]);
            rrddim_set_by_pointer(st, rd_idle, cp_time[4]);
            rrdset_done(st);
        }
    }

    return 0;
}