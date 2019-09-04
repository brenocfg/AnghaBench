#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usec_t ;
struct TYPE_4__ {unsigned long long tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_3__ {unsigned long long tv_sec; scalar_t__ tv_usec; } ;
struct rusage {TYPE_2__ ru_stime; TYPE_1__ ru_utime; } ;
typedef  int /*<<< orphan*/  heartbeat_t ;
typedef  int /*<<< orphan*/  RRDSET ;

/* Variables and functions */
 int /*<<< orphan*/  PLUGIN_CGROUPS_NAME ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  RUSAGE_THREAD ; 
 scalar_t__ USEC_PER_SEC ; 
 scalar_t__ cgroup_check_for_new_every ; 
 int /*<<< orphan*/  cgroup_main_cleanup ; 
 int /*<<< orphan*/  cgroup_root ; 
 scalar_t__ cgroup_update_every ; 
 scalar_t__ cgroups_check ; 
 int config_get_boolean (char*,char*,int) ; 
 int /*<<< orphan*/  find_all_cgroups () ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int /*<<< orphan*/  heartbeat_init (int /*<<< orphan*/ *) ; 
 scalar_t__ heartbeat_next (int /*<<< orphan*/ *,scalar_t__) ; 
 int netdata_exit ; 
 int /*<<< orphan*/  netdata_thread_cleanup_pop (int) ; 
 int /*<<< orphan*/  netdata_thread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  read_all_cgroups (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cgroup_plugin_configuration () ; 
 int /*<<< orphan*/  rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_cgroup_charts (scalar_t__) ; 

void *cgroups_main(void *ptr) {
    netdata_thread_cleanup_push(cgroup_main_cleanup, ptr);

    struct rusage thread;

    // when ZERO, attempt to do it
    int vdo_cpu_netdata = config_get_boolean("plugin:cgroups", "cgroups plugin resource charts", 1);

    read_cgroup_plugin_configuration();

    RRDSET *stcpu_thread = NULL;

    heartbeat_t hb;
    heartbeat_init(&hb);
    usec_t step = cgroup_update_every * USEC_PER_SEC;
    usec_t find_every = cgroup_check_for_new_every * USEC_PER_SEC, find_dt = 0;

    while(!netdata_exit) {
        usec_t hb_dt = heartbeat_next(&hb, step);
        if(unlikely(netdata_exit)) break;

        // BEGIN -- the job to be done

        find_dt += hb_dt;
        if(unlikely(find_dt >= find_every || cgroups_check)) {
            find_all_cgroups();
            find_dt = 0;
            cgroups_check = 0;
        }

        read_all_cgroups(cgroup_root);
        update_cgroup_charts(cgroup_update_every);

        // END -- the job is done

        // --------------------------------------------------------------------

        if(vdo_cpu_netdata) {
            getrusage(RUSAGE_THREAD, &thread);

            if(unlikely(!stcpu_thread)) {

                stcpu_thread = rrdset_create_localhost(
                        "netdata"
                        , "plugin_cgroups_cpu"
                        , NULL
                        , "cgroups"
                        , NULL
                        , "NetData CGroups Plugin CPU usage"
                        , "milliseconds/s"
                        , PLUGIN_CGROUPS_NAME
                        , "stats"
                        , 132000
                        , cgroup_update_every
                        , RRDSET_TYPE_STACKED
                );

                rrddim_add(stcpu_thread, "user",  NULL,  1, 1000, RRD_ALGORITHM_INCREMENTAL);
                rrddim_add(stcpu_thread, "system", NULL, 1, 1000, RRD_ALGORITHM_INCREMENTAL);
            }
            else
                rrdset_next(stcpu_thread);

            rrddim_set(stcpu_thread, "user"  , thread.ru_utime.tv_sec * 1000000ULL + thread.ru_utime.tv_usec);
            rrddim_set(stcpu_thread, "system", thread.ru_stime.tv_sec * 1000000ULL + thread.ru_stime.tv_usec);
            rrdset_done(stcpu_thread);
        }
    }

    netdata_thread_cleanup_pop(1);
    return NULL;
}