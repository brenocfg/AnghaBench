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
typedef  scalar_t__ collected_number ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_UPTIME ; 
 int /*<<< orphan*/  PLUGIN_PROC_NAME ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  info (char*,long long) ; 
 int /*<<< orphan*/  procfile_close (int /*<<< orphan*/ ) ; 
 scalar_t__ read_proc_uptime () ; 
 int /*<<< orphan*/  read_proc_uptime_ff ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ uptime_from_boottime () ; 

int do_proc_uptime(int update_every, usec_t dt) {
    (void)dt;

    static int use_boottime = -1;

    if(unlikely(use_boottime == -1)) {
        collected_number uptime_boottime = uptime_from_boottime();
        collected_number uptime_proc     = read_proc_uptime();

        long long delta = (long long)uptime_boottime - (long long)uptime_proc;
        if(delta < 0) delta = -delta;

        if(delta <= 1000 && uptime_boottime != 0) {
            procfile_close(read_proc_uptime_ff);
            info("Using now_boottime_usec() for uptime (dt is %lld ms)", delta);
            use_boottime = 1;
        }
        else if(uptime_proc != 0) {
            info("Using /proc/uptime for uptime (dt is %lld ms)", delta);
            use_boottime = 0;
        }
        else {
            error("Cannot find any way to read uptime on this system.");
            return 1;
        }
    }

    collected_number uptime;
    if(use_boottime)
        uptime = uptime_from_boottime();
    else
        uptime = read_proc_uptime();


    // --------------------------------------------------------------------

    static RRDSET *st = NULL;
    static RRDDIM *rd = NULL;

    if(unlikely(!st)) {

        st = rrdset_create_localhost(
                "system"
                , "uptime"
                , NULL
                , "uptime"
                , NULL
                , "System Uptime"
                , "seconds"
                , PLUGIN_PROC_NAME
                , "/proc/uptime"
                , NETDATA_CHART_PRIO_SYSTEM_UPTIME
                , update_every
                , RRDSET_TYPE_LINE
        );

        rd = rrddim_add(st, "uptime", NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
    }
    else
        rrdset_next(st);

    rrddim_set_by_pointer(st, rd, uptime);

    rrdset_done(st);

    return 0;
}