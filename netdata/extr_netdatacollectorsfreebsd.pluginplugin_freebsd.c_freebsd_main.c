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
typedef  int usec_t ;
struct freebsd_module {char* name; int enabled; unsigned long long duration; int /*<<< orphan*/ * rd; int /*<<< orphan*/  dim; int /*<<< orphan*/  (* func ) (int,int) ;} ;
typedef  int /*<<< orphan*/  heartbeat_t ;
struct TYPE_2__ {int rrd_update_every; } ;
typedef  int /*<<< orphan*/  RRDSET ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROCNETDEV_LOOP ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int USEC_PER_SEC ; 
 void* config_get_boolean (char*,char*,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  freebsd_main_cleanup ; 
 struct freebsd_module* freebsd_modules ; 
 scalar_t__ freebsd_plugin_init () ; 
 int /*<<< orphan*/  global_statistics_charts () ; 
 int /*<<< orphan*/  heartbeat_init (int /*<<< orphan*/ *) ; 
 int heartbeat_monotonic_dt_to_now_usec (int /*<<< orphan*/ *) ; 
 int heartbeat_next (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* localhost ; 
 int /*<<< orphan*/  netdata_cleanup_and_exit (int) ; 
 int netdata_exit ; 
 int /*<<< orphan*/  netdata_thread_cleanup_pop (int) ; 
 int /*<<< orphan*/  netdata_thread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  registry_statistics () ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rrdset_find_bytype_localhost (char*,char*) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 scalar_t__ unlikely (int) ; 

void *freebsd_main(void *ptr) {
    netdata_thread_cleanup_push(freebsd_main_cleanup, ptr);

    int vdo_cpu_netdata = config_get_boolean("plugin:freebsd", "netdata server resources", 1);

    // initialize FreeBSD plugin
    if (freebsd_plugin_init())
        netdata_cleanup_and_exit(1);

    // check the enabled status for each module
    int i;
    for(i = 0 ; freebsd_modules[i].name ;i++) {
        struct freebsd_module *pm = &freebsd_modules[i];

        pm->enabled = config_get_boolean("plugin:freebsd", pm->name, pm->enabled);
        pm->duration = 0ULL;
        pm->rd = NULL;
    }

    usec_t step = localhost->rrd_update_every * USEC_PER_SEC;
    heartbeat_t hb;
    heartbeat_init(&hb);

    while(!netdata_exit) {
        usec_t hb_dt = heartbeat_next(&hb, step);
        usec_t duration = 0ULL;

        if(unlikely(netdata_exit)) break;

        // BEGIN -- the job to be done

        for(i = 0 ; freebsd_modules[i].name ;i++) {
            struct freebsd_module *pm = &freebsd_modules[i];
            if(unlikely(!pm->enabled)) continue;

            debug(D_PROCNETDEV_LOOP, "FREEBSD calling %s.", pm->name);

            pm->enabled = !pm->func(localhost->rrd_update_every, hb_dt);
            pm->duration = heartbeat_monotonic_dt_to_now_usec(&hb) - duration;
            duration += pm->duration;

            if(unlikely(netdata_exit)) break;
        }

        // END -- the job is done

        // --------------------------------------------------------------------

        if(vdo_cpu_netdata) {
            static RRDSET *st = NULL;

            if(unlikely(!st)) {
                st = rrdset_find_bytype_localhost("netdata", "plugin_freebsd_modules");

                if(!st) {
                    st = rrdset_create_localhost(
                            "netdata"
                            , "plugin_freebsd_modules"
                            , NULL
                            , "freebsd"
                            , NULL
                            , "NetData FreeBSD Plugin Modules Durations"
                            , "milliseconds/run"
                            , "netdata"
                            , "stats"
                            , 132001
                            , localhost->rrd_update_every
                            , RRDSET_TYPE_STACKED
                    );

                    for(i = 0 ; freebsd_modules[i].name ;i++) {
                        struct freebsd_module *pm = &freebsd_modules[i];
                        if(unlikely(!pm->enabled)) continue;

                        pm->rd = rrddim_add(st, pm->dim, NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
                    }
                }
            }
            else rrdset_next(st);

            for(i = 0 ; freebsd_modules[i].name ;i++) {
                struct freebsd_module *pm = &freebsd_modules[i];
                if(unlikely(!pm->enabled)) continue;

                rrddim_set_by_pointer(st, pm->rd, pm->duration);
            }
            rrdset_done(st);

            global_statistics_charts();
            registry_statistics();
        }
    }

    netdata_thread_cleanup_pop(1);
    return NULL;
}