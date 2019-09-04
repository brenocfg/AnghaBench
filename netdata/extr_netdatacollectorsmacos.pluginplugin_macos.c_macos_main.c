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
typedef  int /*<<< orphan*/  heartbeat_t ;
struct TYPE_2__ {int rrd_update_every; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROCNETDEV_LOOP ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  config_get_boolean (char*,char*,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*) ; 
 int do_macos_iokit (int,int) ; 
 int do_macos_mach_smi (int,int) ; 
 int do_macos_sysctl (int,int) ; 
 int /*<<< orphan*/  global_statistics_charts () ; 
 int /*<<< orphan*/  heartbeat_init (int /*<<< orphan*/ *) ; 
 int heartbeat_next (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* localhost ; 
 int /*<<< orphan*/  macos_main_cleanup ; 
 int /*<<< orphan*/  netdata_exit ; 
 int /*<<< orphan*/  netdata_thread_cleanup_pop (int) ; 
 int /*<<< orphan*/  netdata_thread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  registry_statistics () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void *macos_main(void *ptr) {
    netdata_thread_cleanup_push(macos_main_cleanup, ptr);

    // when ZERO, attempt to do it
    int vdo_cpu_netdata             = !config_get_boolean("plugin:macos", "netdata server resources", 1);
    int vdo_macos_sysctl            = !config_get_boolean("plugin:macos", "sysctl", 1);
    int vdo_macos_mach_smi          = !config_get_boolean("plugin:macos", "mach system management interface", 1);
    int vdo_macos_iokit             = !config_get_boolean("plugin:macos", "iokit", 1);

    // keep track of the time each module was called
    unsigned long long sutime_macos_sysctl = 0ULL;
    unsigned long long sutime_macos_mach_smi = 0ULL;
    unsigned long long sutime_macos_iokit = 0ULL;

    usec_t step = localhost->rrd_update_every * USEC_PER_SEC;
    heartbeat_t hb;
    heartbeat_init(&hb);

    while(!netdata_exit) {
        usec_t hb_dt = heartbeat_next(&hb, step);

        if(unlikely(netdata_exit)) break;

        // BEGIN -- the job to be done

        if(!vdo_macos_sysctl) {
            debug(D_PROCNETDEV_LOOP, "MACOS: calling do_macos_sysctl().");
            vdo_macos_sysctl = do_macos_sysctl(localhost->rrd_update_every, hb_dt);
        }
        if(unlikely(netdata_exit)) break;

        if(!vdo_macos_mach_smi) {
            debug(D_PROCNETDEV_LOOP, "MACOS: calling do_macos_mach_smi().");
            vdo_macos_mach_smi = do_macos_mach_smi(localhost->rrd_update_every, hb_dt);
        }
        if(unlikely(netdata_exit)) break;

        if(!vdo_macos_iokit) {
            debug(D_PROCNETDEV_LOOP, "MACOS: calling do_macos_iokit().");
            vdo_macos_iokit = do_macos_iokit(localhost->rrd_update_every, hb_dt);
        }
        if(unlikely(netdata_exit)) break;

        // END -- the job is done

        // --------------------------------------------------------------------

        if(!vdo_cpu_netdata) {
            global_statistics_charts();
            registry_statistics();
        }
    }

    netdata_thread_cleanup_pop(1);
    return NULL;
}