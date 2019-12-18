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
struct vmtotal {scalar_t__ t_rm; scalar_t__ t_pw; scalar_t__ t_dw; scalar_t__ t_rq; scalar_t__ t_sw; scalar_t__ t_sl; } ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int GETSYSCTL_SIMPLE (char*,int*,struct vmtotal) ; 
 int MEGA_FACTOR ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_MEM_SYSTEM_COMMITTED ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_ACTIVE_PROCESSES ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_PROCESSES ; 
 int /*<<< orphan*/  RRDSET_FLAG_DETAIL ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int config_get_boolean (char*,char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_flag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int system_pagesize ; 
 scalar_t__ unlikely (int) ; 

int do_vm_vmtotal(int update_every, usec_t dt) {
    (void)dt;
    static int do_all_processes = -1, do_processes = -1, do_committed = -1;

    if (unlikely(do_all_processes == -1)) {
        do_all_processes    = config_get_boolean("plugin:freebsd:vm.vmtotal", "enable total processes", 1);
        do_processes        = config_get_boolean("plugin:freebsd:vm.vmtotal", "processes running", 1);
        do_committed        = config_get_boolean("plugin:freebsd:vm.vmtotal", "committed memory", 1);
    }

    if (likely(do_all_processes | do_processes | do_committed)) {
        static int mib[2] = {0, 0};
        struct vmtotal vmtotal_data;

        if (unlikely(GETSYSCTL_SIMPLE("vm.vmtotal", mib, vmtotal_data))) {
            do_all_processes = 0;
            error("DISABLED: system.active_processes chart");
            do_processes = 0;
            error("DISABLED: system.processes chart");
            do_committed = 0;
            error("DISABLED: mem.committed chart");
            error("DISABLED: vm.vmtotal module");
            return 1;
        } else {

            // --------------------------------------------------------------------

            if (likely(do_all_processes)) {
                static RRDSET *st = NULL;
                static RRDDIM *rd = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "system",
                            "active_processes",
                            NULL,
                            "processes",
                            NULL,
                            "System Active Processes",
                            "processes",
                            "freebsd.plugin",
                            "vm.vmtotal",
                            NETDATA_CHART_PRIO_SYSTEM_ACTIVE_PROCESSES,
                            update_every,
                            RRDSET_TYPE_LINE
                    );
                    rd = rrddim_add(st, "active", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
                }
                else rrdset_next(st);

                rrddim_set_by_pointer(st, rd, (vmtotal_data.t_rq + vmtotal_data.t_dw + vmtotal_data.t_pw + vmtotal_data.t_sl + vmtotal_data.t_sw));
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (likely(do_processes)) {
                static RRDSET *st = NULL;
                static RRDDIM *rd_running = NULL, *rd_blocked = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "system",
                            "processes",
                            NULL,
                            "processes",
                            NULL,
                            "System Processes",
                            "processes",
                            "freebsd.plugin",
                            "vm.vmtotal",
                            NETDATA_CHART_PRIO_SYSTEM_PROCESSES,
                            update_every,
                            RRDSET_TYPE_LINE
                    );

                    rd_running = rrddim_add(st, "running", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
                    rd_blocked = rrddim_add(st, "blocked", NULL, -1, 1, RRD_ALGORITHM_ABSOLUTE);
                }
                else rrdset_next(st);

                rrddim_set_by_pointer(st, rd_running, vmtotal_data.t_rq);
                rrddim_set_by_pointer(st, rd_blocked, (vmtotal_data.t_dw + vmtotal_data.t_pw));
                rrdset_done(st);
            }

            // --------------------------------------------------------------------

            if (likely(do_committed)) {
                static RRDSET *st = NULL;
                static RRDDIM *rd = NULL;

                if (unlikely(!st)) {
                    st = rrdset_create_localhost(
                            "mem",
                            "committed",
                            NULL,
                            "system",
                            NULL,
                            "Committed (Allocated) Memory",
                            "MiB",
                            "freebsd.plugin",
                            "vm.vmtotal",
                            NETDATA_CHART_PRIO_MEM_SYSTEM_COMMITTED,
                            update_every,
                            RRDSET_TYPE_AREA
                    );
                    rrdset_flag_set(st, RRDSET_FLAG_DETAIL);

                    rd = rrddim_add(st, "Committed_AS", NULL, system_pagesize, MEGA_FACTOR, RRD_ALGORITHM_ABSOLUTE);
                }
                else rrdset_next(st);

                rrddim_set_by_pointer(st, rd, vmtotal_data.t_rm);
                rrdset_done(st);
            }
        }
    } else {
        error("DISABLED: vm.vmtotal module");
        return 1;
    }

    return 0;
}