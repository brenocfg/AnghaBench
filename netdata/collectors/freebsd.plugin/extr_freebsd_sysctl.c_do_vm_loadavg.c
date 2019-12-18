#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int usec_t ;
struct loadavg {double fscale; scalar_t__* ldavg; } ;
typedef  int /*<<< orphan*/  collected_number ;
struct TYPE_7__ {int update_every; } ;
typedef  TYPE_1__ RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int GETSYSCTL_SIMPLE (char*,int*,struct loadavg) ; 
 int MIN_LOADAVG_UPDATE_EVERY ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_LOAD ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * rrddim_add (TYPE_1__*,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdset_next (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

int do_vm_loadavg(int update_every, usec_t dt){
    static usec_t next_loadavg_dt = 0;

    if (next_loadavg_dt <= dt) {
        static int mib[2] = {0, 0};
        struct loadavg sysload;

        if (unlikely(GETSYSCTL_SIMPLE("vm.loadavg", mib, sysload))) {
            error("DISABLED: system.load chart");
            error("DISABLED: vm.loadavg module");
            return 1;
        } else {

            // --------------------------------------------------------------------

            static RRDSET *st = NULL;
            static RRDDIM *rd_load1 = NULL, *rd_load2 = NULL, *rd_load3 = NULL;

            if (unlikely(!st)) {
                st = rrdset_create_localhost(
                        "system",
                        "load",
                        NULL,
                        "load",
                        NULL,
                        "System Load Average",
                        "load",
                        "freebsd.plugin",
                        "vm.loadavg",
                        NETDATA_CHART_PRIO_SYSTEM_LOAD,
                        (update_every < MIN_LOADAVG_UPDATE_EVERY) ?
                        MIN_LOADAVG_UPDATE_EVERY : update_every, RRDSET_TYPE_LINE
                );
                rd_load1 = rrddim_add(st, "load1", NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
                rd_load2 = rrddim_add(st, "load5", NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
                rd_load3 = rrddim_add(st, "load15", NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
            } else
                rrdset_next(st);

            rrddim_set_by_pointer(st, rd_load1, (collected_number) ((double) sysload.ldavg[0] / sysload.fscale * 1000));
            rrddim_set_by_pointer(st, rd_load2, (collected_number) ((double) sysload.ldavg[1] / sysload.fscale * 1000));
            rrddim_set_by_pointer(st, rd_load3, (collected_number) ((double) sysload.ldavg[2] / sysload.fscale * 1000));
            rrdset_done(st);

            next_loadavg_dt = st->update_every * USEC_PER_SEC;
        }
    }
    else
        next_loadavg_dt -= dt;

    return 0;
}