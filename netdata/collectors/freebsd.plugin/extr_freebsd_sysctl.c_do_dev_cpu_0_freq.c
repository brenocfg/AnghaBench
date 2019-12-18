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
 int GETSYSCTL_SIMPLE (char*,int*,int) ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_CPUFREQ_SCALING_CUR_FREQ ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_dev_cpu_0_freq(int update_every, usec_t dt) {
    (void)dt;
    static int mib[4] = {0, 0, 0, 0};
    int cpufreq;

    if (unlikely(GETSYSCTL_SIMPLE("dev.cpu.0.freq", mib, cpufreq))) {
        error("DISABLED: cpu.scaling_cur_freq chart");
        error("DISABLED: dev.cpu.0.freq module");
        return 1;
    } else {

        // --------------------------------------------------------------------

        static RRDSET *st = NULL;
        static RRDDIM *rd = NULL;

        if (unlikely(!st)) {
            st = rrdset_create_localhost(
                    "cpu",
                    "scaling_cur_freq",
                    NULL,
                    "cpufreq",
                    NULL,
                    "Current CPU Scaling Frequency",
                    "MHz",
                    "freebsd.plugin",
                    "dev.cpu.0.freq",
                    NETDATA_CHART_PRIO_CPUFREQ_SCALING_CUR_FREQ,
                    update_every,
                    RRDSET_TYPE_LINE
            );

            rd = rrddim_add(st, "frequency", NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(st);

        rrddim_set_by_pointer(st, rd, cpufreq);
        rrdset_done(st);
    }

    return 0;
}