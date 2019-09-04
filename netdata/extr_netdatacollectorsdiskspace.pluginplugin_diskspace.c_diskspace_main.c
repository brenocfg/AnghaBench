#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int usec_t ;
struct TYPE_5__ {unsigned long long tv_sec; int tv_usec; } ;
struct TYPE_4__ {unsigned long long tv_sec; int tv_usec; } ;
struct rusage {TYPE_2__ ru_stime; TYPE_1__ ru_utime; } ;
struct mountinfo {int flags; struct mountinfo* next; } ;
typedef  int /*<<< orphan*/  heartbeat_t ;
struct TYPE_6__ {int rrd_update_every; } ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 char* CONFIG_SECTION_DISKSPACE ; 
 int MOUNTINFO_IS_BIND ; 
 int MOUNTINFO_IS_DUMMY ; 
 int NETDATA_CHART_PRIO_NETDATA_DISKSPACE ; 
 int /*<<< orphan*/  PLUGIN_DISKSPACE_NAME ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  RUSAGE_THREAD ; 
 int USEC_PER_SEC ; 
 int check_for_new_mountpoints_every ; 
 int cleanup_mount_points ; 
 int config_get_boolean (char*,char*,int) ; 
 scalar_t__ config_get_number (char*,char*,int) ; 
 scalar_t__ dict_mountpoints ; 
 int /*<<< orphan*/  dictionary_get_all (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mountinfo* disk_mountinfo_root ; 
 int /*<<< orphan*/  diskspace_main_cleanup ; 
 int /*<<< orphan*/  do_disk_space_stats (struct mountinfo*,int) ; 
 int /*<<< orphan*/  getrusage (int /*<<< orphan*/ ,struct rusage*) ; 
 int /*<<< orphan*/  heartbeat_init (int /*<<< orphan*/ *) ; 
 int heartbeat_monotonic_dt_to_now_usec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heartbeat_next (int /*<<< orphan*/ *,int) ; 
 TYPE_3__* localhost ; 
 int /*<<< orphan*/  mount_point_cleanup ; 
 int /*<<< orphan*/  mountinfo_reload (int /*<<< orphan*/ ) ; 
 int netdata_exit ; 
 int /*<<< orphan*/  netdata_thread_cleanup_pop (int) ; 
 int /*<<< orphan*/  netdata_thread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void *diskspace_main(void *ptr) {
    netdata_thread_cleanup_push(diskspace_main_cleanup, ptr);

    int vdo_cpu_netdata = config_get_boolean("plugin:proc", "netdata server resources", 1);

    cleanup_mount_points = config_get_boolean(CONFIG_SECTION_DISKSPACE, "remove charts of unmounted disks" , cleanup_mount_points);

    int update_every = (int)config_get_number(CONFIG_SECTION_DISKSPACE, "update every", localhost->rrd_update_every);
    if(update_every < localhost->rrd_update_every)
        update_every = localhost->rrd_update_every;

    check_for_new_mountpoints_every = (int)config_get_number(CONFIG_SECTION_DISKSPACE, "check for new mount points every", check_for_new_mountpoints_every);
    if(check_for_new_mountpoints_every < update_every)
        check_for_new_mountpoints_every = update_every;

    struct rusage thread;

    usec_t duration = 0;
    usec_t step = update_every * USEC_PER_SEC;
    heartbeat_t hb;
    heartbeat_init(&hb);
    while(!netdata_exit) {
        duration = heartbeat_monotonic_dt_to_now_usec(&hb);
        /* usec_t hb_dt = */ heartbeat_next(&hb, step);

        if(unlikely(netdata_exit)) break;


        // --------------------------------------------------------------------------
        // this is smart enough not to reload it every time

        mountinfo_reload(0);


        // --------------------------------------------------------------------------
        // disk space metrics

        struct mountinfo *mi;
        for(mi = disk_mountinfo_root; mi; mi = mi->next) {

            if(unlikely(mi->flags & (MOUNTINFO_IS_DUMMY | MOUNTINFO_IS_BIND)))
                continue;

            do_disk_space_stats(mi, update_every);
            if(unlikely(netdata_exit)) break;
        }

        if(unlikely(netdata_exit)) break;

        if(dict_mountpoints)
            dictionary_get_all(dict_mountpoints, mount_point_cleanup, NULL);

        if(vdo_cpu_netdata) {
            static RRDSET *stcpu_thread = NULL, *st_duration = NULL;
            static RRDDIM *rd_user = NULL, *rd_system = NULL, *rd_duration = NULL;

            // ----------------------------------------------------------------

            getrusage(RUSAGE_THREAD, &thread);

            if(unlikely(!stcpu_thread)) {
                stcpu_thread = rrdset_create_localhost(
                        "netdata"
                        , "plugin_diskspace"
                        , NULL
                        , "diskspace"
                        , NULL
                        , "NetData Disk Space Plugin CPU usage"
                        , "milliseconds/s"
                        , PLUGIN_DISKSPACE_NAME
                        , NULL
                        , NETDATA_CHART_PRIO_NETDATA_DISKSPACE
                        , update_every
                        , RRDSET_TYPE_STACKED
                );

                rd_user   = rrddim_add(stcpu_thread, "user", NULL, 1, 1000, RRD_ALGORITHM_INCREMENTAL);
                rd_system = rrddim_add(stcpu_thread, "system", NULL, 1, 1000, RRD_ALGORITHM_INCREMENTAL);
            }
            else
                rrdset_next(stcpu_thread);

            rrddim_set_by_pointer(stcpu_thread, rd_user, thread.ru_utime.tv_sec * 1000000ULL + thread.ru_utime.tv_usec);
            rrddim_set_by_pointer(stcpu_thread, rd_system, thread.ru_stime.tv_sec * 1000000ULL + thread.ru_stime.tv_usec);
            rrdset_done(stcpu_thread);

            // ----------------------------------------------------------------

            if(unlikely(!st_duration)) {
                st_duration = rrdset_create_localhost(
                        "netdata"
                        , "plugin_diskspace_dt"
                        , NULL
                        , "diskspace"
                        , NULL
                        , "NetData Disk Space Plugin Duration"
                        , "milliseconds/run"
                        , PLUGIN_DISKSPACE_NAME
                        , NULL
                        , 132021
                        , update_every
                        , RRDSET_TYPE_AREA
                );

                rd_duration = rrddim_add(st_duration, "duration", NULL, 1, 1000, RRD_ALGORITHM_ABSOLUTE);
            }
            else
                rrdset_next(st_duration);

            rrddim_set_by_pointer(st_duration, rd_duration, duration);
            rrdset_done(st_duration);

            // ----------------------------------------------------------------

            if(unlikely(netdata_exit)) break;
        }
    }

    netdata_thread_cleanup_pop(1);
    return NULL;
}