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
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_UPTIME ; 
 int /*<<< orphan*/  PLUGIN_PROC_NAME ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 char* config_get (char*,char*,char*) ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  uptime_msec (char*) ; 

int do_proc_uptime(int update_every, usec_t dt) {
    (void)dt;

    static char *uptime_filename = NULL;
    if(!uptime_filename) {
        char filename[FILENAME_MAX + 1];
        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/proc/uptime");

        uptime_filename = config_get("plugin:proc:/proc/uptime", "filename to monitor", filename);
    }

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

    rrddim_set_by_pointer(st, rd, uptime_msec(uptime_filename));

    rrdset_done(st);

    return 0;
}