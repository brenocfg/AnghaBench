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
typedef  int /*<<< orphan*/  procfile ;
typedef  unsigned long long collected_number ;
struct TYPE_7__ {int update_every; } ;
typedef  TYPE_1__ RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SECTION_PLUGIN_PROC_LOADAVG ; 
 int /*<<< orphan*/  FILENAME_MAX ; 
 int MIN_LOADAVG_UPDATE_EVERY ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_ACTIVE_PROCESSES ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_LOAD ; 
 int /*<<< orphan*/  PLUGIN_PROC_MODULE_LOADAVG_NAME ; 
 int /*<<< orphan*/  PLUGIN_PROC_NAME ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  config_get (int /*<<< orphan*/ ,char*,char*) ; 
 int config_get_boolean (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 int procfile_lines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfile_lineword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int procfile_linewords (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rrddim_add (TYPE_1__*,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (TYPE_1__*,int /*<<< orphan*/ *,unsigned long long) ; 
 TYPE_1__* rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdset_next (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 unsigned long long str2ull (int /*<<< orphan*/ ) ; 
 double strtod (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_proc_loadavg(int update_every, usec_t dt) {
    static procfile *ff = NULL;
    static int do_loadavg = -1, do_all_processes = -1;
    static usec_t next_loadavg_dt = 0;

    if(unlikely(!ff)) {
        char filename[FILENAME_MAX + 1];
        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/proc/loadavg");

        ff = procfile_open(config_get(CONFIG_SECTION_PLUGIN_PROC_LOADAVG, "filename to monitor", filename), " \t,:|/", PROCFILE_FLAG_DEFAULT);
        if(unlikely(!ff))
            return 1;
    }

    ff = procfile_readall(ff);
    if(unlikely(!ff))
        return 0; // we return 0, so that we will retry to open it next time

    if(unlikely(do_loadavg == -1)) {
        do_loadavg          = config_get_boolean(CONFIG_SECTION_PLUGIN_PROC_LOADAVG, "enable load average", 1);
        do_all_processes    = config_get_boolean(CONFIG_SECTION_PLUGIN_PROC_LOADAVG, "enable total processes", 1);
    }

    if(unlikely(procfile_lines(ff) < 1)) {
        error("/proc/loadavg has no lines.");
        return 1;
    }
    if(unlikely(procfile_linewords(ff, 0) < 6)) {
        error("/proc/loadavg has less than 6 words in it.");
        return 1;
    }

    double load1 = strtod(procfile_lineword(ff, 0, 0), NULL);
    double load5 = strtod(procfile_lineword(ff, 0, 1), NULL);
    double load15 = strtod(procfile_lineword(ff, 0, 2), NULL);

    //unsigned long long running_processes  = str2ull(procfile_lineword(ff, 0, 3));
    unsigned long long active_processes     = str2ull(procfile_lineword(ff, 0, 4));
    //unsigned long long next_pid           = str2ull(procfile_lineword(ff, 0, 5));


    // --------------------------------------------------------------------

    if(next_loadavg_dt <= dt) {
        if(likely(do_loadavg)) {
            static RRDSET *load_chart = NULL;
            static RRDDIM *rd_load1 = NULL, *rd_load5 = NULL, *rd_load15 = NULL;

            if(unlikely(!load_chart)) {
                load_chart = rrdset_create_localhost(
                        "system"
                        , "load"
                        , NULL
                        , "load"
                        , NULL
                        , "System Load Average"
                        , "load"
                        , PLUGIN_PROC_NAME
                        , PLUGIN_PROC_MODULE_LOADAVG_NAME
                        , NETDATA_CHART_PRIO_SYSTEM_LOAD
                        , (update_every < MIN_LOADAVG_UPDATE_EVERY) ? MIN_LOADAVG_UPDATE_EVERY : update_every
                        , RRDSET_TYPE_LINE
                );

                rd_load1  = rrddim_add(load_chart, "load1",  NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
                rd_load5  = rrddim_add(load_chart, "load5",  NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
                rd_load15 = rrddim_add(load_chart, "load15", NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
            }
            else
                rrdset_next(load_chart);

            rrddim_set_by_pointer(load_chart, rd_load1, (collected_number) (load1 * 1000));
            rrddim_set_by_pointer(load_chart, rd_load5, (collected_number) (load5 * 1000));
            rrddim_set_by_pointer(load_chart, rd_load15, (collected_number) (load15 * 1000));
            rrdset_done(load_chart);

            next_loadavg_dt = load_chart->update_every * USEC_PER_SEC;
        }
        else next_loadavg_dt =  MIN_LOADAVG_UPDATE_EVERY * USEC_PER_SEC;
    }
    else next_loadavg_dt -= dt;

    // --------------------------------------------------------------------

    if(likely(do_all_processes)) {
        static RRDSET *processes_chart = NULL;
        static RRDDIM *rd_active = NULL;

        if(unlikely(!processes_chart)) {
            processes_chart = rrdset_create_localhost(
                    "system"
                    , "active_processes"
                    , NULL
                    , "processes"
                    , NULL
                    , "System Active Processes"
                    , "processes"
                    , PLUGIN_PROC_NAME
                    , PLUGIN_PROC_MODULE_LOADAVG_NAME
                    , NETDATA_CHART_PRIO_SYSTEM_ACTIVE_PROCESSES
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_active = rrddim_add(processes_chart, "active", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else rrdset_next(processes_chart);

        rrddim_set_by_pointer(processes_chart, rd_active, active_processes);
        rrdset_done(processes_chart);
    }

    return 0;
}