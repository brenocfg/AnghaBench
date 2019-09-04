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
struct TYPE_6__ {int bytes_read; int bytes_write; int bytes_free; int operations_read; int operations_write; int operations_other; int operations_free; int duration_read_ms; int duration_write_ms; int duration_other_ms; int duration_free_ms; int busy_time_ms; } ;
struct disk {int updated; int configured; int enabled; scalar_t__ do_io; scalar_t__ do_ops; scalar_t__ do_qops; scalar_t__ do_util; scalar_t__ do_iotime; scalar_t__ do_await; scalar_t__ do_avagsz; scalar_t__ do_svctm; TYPE_3__ prev_dstat; int /*<<< orphan*/ * st_svctm; int /*<<< orphan*/ * rd_svctm; int /*<<< orphan*/ * st_avagsz; int /*<<< orphan*/ * rd_avagsz_free; int /*<<< orphan*/ * rd_avagsz_out; int /*<<< orphan*/ * rd_avagsz_in; int /*<<< orphan*/ * st_await; int /*<<< orphan*/ * rd_await_free; int /*<<< orphan*/ * rd_await_other; int /*<<< orphan*/ * rd_await_out; int /*<<< orphan*/ * rd_await_in; int /*<<< orphan*/ * st_iotime; int /*<<< orphan*/ * rd_iotime_free; int /*<<< orphan*/ * rd_iotime_other; int /*<<< orphan*/ * rd_iotime_out; int /*<<< orphan*/ * rd_iotime_in; int /*<<< orphan*/ * st_util; int /*<<< orphan*/ * rd_util; int /*<<< orphan*/ * st_qops; int /*<<< orphan*/ * rd_qops; int /*<<< orphan*/ * st_ops; int /*<<< orphan*/ * rd_ops_free; int /*<<< orphan*/ * rd_ops_other; int /*<<< orphan*/ * rd_ops_out; int /*<<< orphan*/ * rd_ops_in; int /*<<< orphan*/ * st_io; int /*<<< orphan*/ * rd_io_free; int /*<<< orphan*/ * rd_io_out; int /*<<< orphan*/ * rd_io_in; } ;
struct TYPE_5__ {int sec; double frac; } ;
struct devstat {int device_type; int* bytes; char* device_name; int* operations; int start_count; int end_count; TYPE_2__ busy_time; TYPE_1__* duration; int /*<<< orphan*/  unit_number; } ;
typedef  int collected_number ;
struct TYPE_4__ {int sec; double frac; } ;
typedef  int /*<<< orphan*/  SIMPLE_PATTERN ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 scalar_t__ CONFIG_BOOLEAN_AUTO ; 
 scalar_t__ CONFIG_BOOLEAN_YES ; 
 size_t DEVSTAT_FREE ; 
 scalar_t__ DEVSTAT_NAME_LEN ; 
 size_t DEVSTAT_NO_DATA ; 
 size_t DEVSTAT_READ ; 
 int DEVSTAT_TYPE_DIRECT ; 
 int DEVSTAT_TYPE_MASK ; 
 int DEVSTAT_TYPE_PASS ; 
 int DEVSTAT_TYPE_STORARRAY ; 
 size_t DEVSTAT_WRITE ; 
 int GETSYSCTL_SIMPLE (char*,int*,int) ; 
 int GETSYSCTL_WSIZE (char*,int*,void*,int) ; 
 int KILO_FACTOR ; 
 scalar_t__ MAX_INT_DIGITS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISK_AVGSZ ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISK_AWAIT ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISK_IO ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISK_IOTIME ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISK_OPS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISK_QOPS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISK_SVCTM ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_DISK_UTIL ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_IO ; 
 int /*<<< orphan*/  RRDSET_FLAG_DETAIL ; 
 int /*<<< orphan*/  RRDSET_TYPE_AREA ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  SIMPLE_PATTERN_EXACT ; 
 int /*<<< orphan*/  config_get (char*,char*,char*) ; 
 void* config_get_boolean_ondemand (char*,char*,int) ; 
 int /*<<< orphan*/  disks_cleanup () ; 
 scalar_t__ disks_found ; 
 int /*<<< orphan*/  error (char*) ; 
 struct disk* get_disk (char*) ; 
 scalar_t__ likely (int) ; 
 void* reallocz (void*,int) ; 
 void* rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_flag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * simple_pattern_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_pattern_matches (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int do_kern_devstat(int update_every, usec_t dt) {

#define DELAULT_EXLUDED_DISKS ""
#define CONFIG_SECTION_KERN_DEVSTAT "plugin:freebsd:kern.devstat"
#define BINTIME_SCALE 5.42101086242752217003726400434970855712890625e-17 // this is 1000/2^64

    static int enable_new_disks = -1;
    static int enable_pass_devices = -1, do_system_io = -1, do_io = -1, do_ops = -1, do_qops = -1, do_util = -1,
            do_iotime = -1, do_await = -1, do_avagsz = -1, do_svctm = -1;
    static SIMPLE_PATTERN *excluded_disks = NULL;

    if (unlikely(enable_new_disks == -1)) {
        enable_new_disks = config_get_boolean_ondemand(CONFIG_SECTION_KERN_DEVSTAT,
                                                       "enable new disks detected at runtime", CONFIG_BOOLEAN_AUTO);

        enable_pass_devices = config_get_boolean_ondemand(CONFIG_SECTION_KERN_DEVSTAT,
                                                          "performance metrics for pass devices", CONFIG_BOOLEAN_AUTO);

        do_system_io = config_get_boolean_ondemand(CONFIG_SECTION_KERN_DEVSTAT, "total bandwidth for all disks",
                                                   CONFIG_BOOLEAN_YES);

        do_io     = config_get_boolean_ondemand(CONFIG_SECTION_KERN_DEVSTAT, "bandwidth for all disks",
                                                CONFIG_BOOLEAN_AUTO);
        do_ops    = config_get_boolean_ondemand(CONFIG_SECTION_KERN_DEVSTAT, "operations for all disks",
                                                CONFIG_BOOLEAN_AUTO);
        do_qops   = config_get_boolean_ondemand(CONFIG_SECTION_KERN_DEVSTAT, "queued operations for all disks",
                                                CONFIG_BOOLEAN_AUTO);
        do_util   = config_get_boolean_ondemand(CONFIG_SECTION_KERN_DEVSTAT, "utilization percentage for all disks",
                                                CONFIG_BOOLEAN_AUTO);
        do_iotime = config_get_boolean_ondemand(CONFIG_SECTION_KERN_DEVSTAT, "i/o time for all disks",
                                                CONFIG_BOOLEAN_AUTO);
        do_await  = config_get_boolean_ondemand(CONFIG_SECTION_KERN_DEVSTAT, "average completed i/o time for all disks",
                                                CONFIG_BOOLEAN_AUTO);
        do_avagsz = config_get_boolean_ondemand(CONFIG_SECTION_KERN_DEVSTAT, "average completed i/o bandwidth for all disks",
                                                CONFIG_BOOLEAN_AUTO);
        do_svctm  = config_get_boolean_ondemand(CONFIG_SECTION_KERN_DEVSTAT, "average service time for all disks",
                                                CONFIG_BOOLEAN_AUTO);

        excluded_disks = simple_pattern_create(
                config_get(CONFIG_SECTION_KERN_DEVSTAT, "disable by default disks matching", DELAULT_EXLUDED_DISKS)
                , NULL
                , SIMPLE_PATTERN_EXACT
        );
    }

    if (likely(do_system_io || do_io || do_ops || do_qops || do_util || do_iotime || do_await || do_avagsz || do_svctm)) {
        static int mib_numdevs[3] = {0, 0, 0};
        int numdevs;
        int common_error = 0;

        if (unlikely(GETSYSCTL_SIMPLE("kern.devstat.numdevs", mib_numdevs, numdevs))) {
            common_error = 1;
        } else {
            static int mib_devstat[3] = {0, 0, 0};
            static void *devstat_data = NULL;
            static int old_numdevs = 0;

            if (unlikely(numdevs != old_numdevs)) {
                devstat_data = reallocz(devstat_data, sizeof(long) + sizeof(struct devstat) *
                                                                     numdevs); // there is generation number before devstat structures
                old_numdevs = numdevs;
            }
            if (unlikely(GETSYSCTL_WSIZE("kern.devstat.all", mib_devstat, devstat_data,
                                         sizeof(long) + sizeof(struct devstat) * numdevs))) {
                common_error = 1;
            } else {
                struct devstat *dstat;
                int i;
                collected_number total_disk_kbytes_read = 0;
                collected_number total_disk_kbytes_write = 0;

                disks_found = 0;

                dstat = (struct devstat*)((char*)devstat_data + sizeof(long)); // skip generation number

                for (i = 0; i < numdevs; i++) {
                    if (likely(do_system_io)) {
                        if (((dstat[i].device_type & DEVSTAT_TYPE_MASK) == DEVSTAT_TYPE_DIRECT) ||
                            ((dstat[i].device_type & DEVSTAT_TYPE_MASK) == DEVSTAT_TYPE_STORARRAY)) {
                            total_disk_kbytes_read += dstat[i].bytes[DEVSTAT_READ] / KILO_FACTOR;
                            total_disk_kbytes_write += dstat[i].bytes[DEVSTAT_WRITE] / KILO_FACTOR;
                        }
                    }

                    if (unlikely(!enable_pass_devices))
                        if ((dstat[i].device_type & DEVSTAT_TYPE_PASS) == DEVSTAT_TYPE_PASS)
                            continue;

                    if (((dstat[i].device_type & DEVSTAT_TYPE_MASK) == DEVSTAT_TYPE_DIRECT) ||
                        ((dstat[i].device_type & DEVSTAT_TYPE_MASK) == DEVSTAT_TYPE_STORARRAY)) {
                        char disk[DEVSTAT_NAME_LEN + MAX_INT_DIGITS + 1];
                        struct cur_dstat {
                            collected_number duration_read_ms;
                            collected_number duration_write_ms;
                            collected_number duration_other_ms;
                            collected_number duration_free_ms;
                            collected_number busy_time_ms;
                        } cur_dstat;

                        sprintf(disk, "%s%d", dstat[i].device_name, dstat[i].unit_number);

                        struct disk *dm = get_disk(disk);
                        dm->updated = 1;
                        disks_found++;

                        if(unlikely(!dm->configured)) {
                            char var_name[4096 + 1];

                            // this is the first time we see this disk

                            // remember we configured it
                            dm->configured = 1;

                            dm->enabled = enable_new_disks;

                            if (likely(dm->enabled))
                                dm->enabled = !simple_pattern_matches(excluded_disks, disk);

                            snprintfz(var_name, 4096, "%s:%s", CONFIG_SECTION_KERN_DEVSTAT, disk);
                            dm->enabled = config_get_boolean_ondemand(var_name, "enabled", dm->enabled);

                            dm->do_io     = config_get_boolean_ondemand(var_name, "bandwidth",               do_io);
                            dm->do_ops    = config_get_boolean_ondemand(var_name, "operations",              do_ops);
                            dm->do_qops   = config_get_boolean_ondemand(var_name, "queued operations",       do_qops);
                            dm->do_util   = config_get_boolean_ondemand(var_name, "utilization percentage",  do_util);
                            dm->do_iotime = config_get_boolean_ondemand(var_name, "i/o time",                do_iotime);
                            dm->do_await  = config_get_boolean_ondemand(var_name, "average completed i/o time",
                                                                        do_await);
                            dm->do_avagsz = config_get_boolean_ondemand(var_name, "average completed i/o bandwidth",
                                                                        do_avagsz);
                            dm->do_svctm  = config_get_boolean_ondemand(var_name, "average service time",    do_svctm);

                            // initialise data for differential charts

                            dm->prev_dstat.bytes_read        = dstat[i].bytes[DEVSTAT_READ];
                            dm->prev_dstat.bytes_write       = dstat[i].bytes[DEVSTAT_WRITE];
                            dm->prev_dstat.bytes_free        = dstat[i].bytes[DEVSTAT_FREE];
                            dm->prev_dstat.operations_read   = dstat[i].operations[DEVSTAT_READ];
                            dm->prev_dstat.operations_write  = dstat[i].operations[DEVSTAT_WRITE];
                            dm->prev_dstat.operations_other  = dstat[i].operations[DEVSTAT_NO_DATA];
                            dm->prev_dstat.operations_free   = dstat[i].operations[DEVSTAT_FREE];
                            dm->prev_dstat.duration_read_ms  = dstat[i].duration[DEVSTAT_READ].sec * 1000
                                                               + dstat[i].duration[DEVSTAT_READ].frac * BINTIME_SCALE;
                            dm->prev_dstat.duration_write_ms = dstat[i].duration[DEVSTAT_WRITE].sec * 1000
                                                               + dstat[i].duration[DEVSTAT_WRITE].frac * BINTIME_SCALE;
                            dm->prev_dstat.duration_other_ms = dstat[i].duration[DEVSTAT_NO_DATA].sec * 1000
                                                               + dstat[i].duration[DEVSTAT_NO_DATA].frac * BINTIME_SCALE;
                            dm->prev_dstat.duration_free_ms  = dstat[i].duration[DEVSTAT_FREE].sec * 1000
                                                               + dstat[i].duration[DEVSTAT_FREE].frac * BINTIME_SCALE;
                            dm->prev_dstat.busy_time_ms      = dstat[i].busy_time.sec * 1000
                                                               + dstat[i].busy_time.frac * BINTIME_SCALE;
                        }

                        cur_dstat.duration_read_ms  = dstat[i].duration[DEVSTAT_READ].sec * 1000
                                                      + dstat[i].duration[DEVSTAT_READ].frac * BINTIME_SCALE;
                        cur_dstat.duration_write_ms = dstat[i].duration[DEVSTAT_WRITE].sec * 1000
                                                      + dstat[i].duration[DEVSTAT_WRITE].frac * BINTIME_SCALE;
                        cur_dstat.duration_other_ms = dstat[i].duration[DEVSTAT_NO_DATA].sec * 1000
                                                      + dstat[i].duration[DEVSTAT_NO_DATA].frac * BINTIME_SCALE;
                        cur_dstat.duration_free_ms  = dstat[i].duration[DEVSTAT_FREE].sec * 1000
                                                      + dstat[i].duration[DEVSTAT_FREE].frac * BINTIME_SCALE;

                        cur_dstat.busy_time_ms = dstat[i].busy_time.sec * 1000 + dstat[i].busy_time.frac * BINTIME_SCALE;

                        // --------------------------------------------------------------------

                        if(dm->do_io == CONFIG_BOOLEAN_YES || (dm->do_io == CONFIG_BOOLEAN_AUTO &&
                                                               (dstat[i].bytes[DEVSTAT_READ] ||
                                                                dstat[i].bytes[DEVSTAT_WRITE] ||
                                                                dstat[i].bytes[DEVSTAT_FREE]))) {
                            if (unlikely(!dm->st_io)) {
                                dm->st_io = rrdset_create_localhost("disk",
                                                                    disk,
                                                                    NULL,
                                                                    disk,
                                                                    "disk.io",
                                                                    "Disk I/O Bandwidth",
                                                                    "KiB/s",
                                                                    "freebsd.plugin",
                                                                    "devstat",
                                                                    NETDATA_CHART_PRIO_DISK_IO,
                                                                    update_every,
                                                                    RRDSET_TYPE_AREA
                                );

                                dm->rd_io_in  = rrddim_add(dm->st_io, "reads",  NULL,  1, KILO_FACTOR,
                                                           RRD_ALGORITHM_INCREMENTAL);
                                dm->rd_io_out = rrddim_add(dm->st_io, "writes", NULL, -1, KILO_FACTOR,
                                                           RRD_ALGORITHM_INCREMENTAL);
                                dm->rd_io_free = rrddim_add(dm->st_io, "frees", NULL, -1, KILO_FACTOR,
                                                           RRD_ALGORITHM_INCREMENTAL);
                            } else
                                rrdset_next(dm->st_io);

                            rrddim_set_by_pointer(dm->st_io, dm->rd_io_in,   dstat[i].bytes[DEVSTAT_READ]);
                            rrddim_set_by_pointer(dm->st_io, dm->rd_io_out,  dstat[i].bytes[DEVSTAT_WRITE]);
                            rrddim_set_by_pointer(dm->st_io, dm->rd_io_free, dstat[i].bytes[DEVSTAT_FREE]);
                            rrdset_done(dm->st_io);
                        }

                        // --------------------------------------------------------------------

                        if(dm->do_ops == CONFIG_BOOLEAN_YES || (dm->do_ops == CONFIG_BOOLEAN_AUTO &&
                                                                (dstat[i].operations[DEVSTAT_READ] ||
                                                                 dstat[i].operations[DEVSTAT_WRITE] ||
                                                                 dstat[i].operations[DEVSTAT_NO_DATA] ||
                                                                 dstat[i].operations[DEVSTAT_FREE]))) {
                            if (unlikely(!dm->st_ops)) {
                                dm->st_ops = rrdset_create_localhost("disk_ops",
                                                                     disk,
                                                                     NULL,
                                                                     disk,
                                                                     "disk.ops",
                                                                     "Disk Completed I/O Operations",
                                                                     "operations/s",
                                                                     "freebsd.plugin",
                                                                     "devstat",
                                                                     NETDATA_CHART_PRIO_DISK_OPS,
                                                                     update_every,
                                                                     RRDSET_TYPE_LINE
                                );

                                rrdset_flag_set(dm->st_ops, RRDSET_FLAG_DETAIL);

                                dm->rd_ops_in   = rrddim_add(dm->st_ops, "reads",  NULL,  1, 1,
                                                             RRD_ALGORITHM_INCREMENTAL);
                                dm->rd_ops_out  = rrddim_add(dm->st_ops, "writes", NULL, -1, 1,
                                                             RRD_ALGORITHM_INCREMENTAL);
                                dm->rd_ops_other = rrddim_add(dm->st_ops, "other", NULL,  1, 1,
                                                             RRD_ALGORITHM_INCREMENTAL);
                                dm->rd_ops_free = rrddim_add(dm->st_ops, "frees",  NULL, -1, 1,
                                                             RRD_ALGORITHM_INCREMENTAL);
                            } else
                                rrdset_next(dm->st_ops);

                            rrddim_set_by_pointer(dm->st_ops, dm->rd_ops_in,    dstat[i].operations[DEVSTAT_READ]);
                            rrddim_set_by_pointer(dm->st_ops, dm->rd_ops_out,   dstat[i].operations[DEVSTAT_WRITE]);
                            rrddim_set_by_pointer(dm->st_ops, dm->rd_ops_other, dstat[i].operations[DEVSTAT_NO_DATA]);
                            rrddim_set_by_pointer(dm->st_ops, dm->rd_ops_free,  dstat[i].operations[DEVSTAT_FREE]);
                            rrdset_done(dm->st_ops);
                        }

                        // --------------------------------------------------------------------

                        if(dm->do_qops == CONFIG_BOOLEAN_YES || (dm->do_qops == CONFIG_BOOLEAN_AUTO &&
                                                                 (dstat[i].start_count || dstat[i].end_count))) {
                            if (unlikely(!dm->st_qops)) {
                                dm->st_qops = rrdset_create_localhost("disk_qops",
                                                                      disk,
                                                                      NULL,
                                                                      disk,
                                                                      "disk.qops",
                                                                      "Disk Current I/O Operations",
                                                                      "operations",
                                                                      "freebsd.plugin",
                                                                      "devstat",
                                                                      NETDATA_CHART_PRIO_DISK_QOPS,
                                                                      update_every,
                                                                      RRDSET_TYPE_LINE
                                );

                                rrdset_flag_set(dm->st_qops, RRDSET_FLAG_DETAIL);

                                dm->rd_qops = rrddim_add(dm->st_qops, "operations", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
                            } else
                                rrdset_next(dm->st_qops);

                            rrddim_set_by_pointer(dm->st_qops, dm->rd_qops, dstat[i].start_count - dstat[i].end_count);
                            rrdset_done(dm->st_qops);
                        }

                        // --------------------------------------------------------------------

                        if(dm->do_util == CONFIG_BOOLEAN_YES || (dm->do_util == CONFIG_BOOLEAN_AUTO &&
                                                                 cur_dstat.busy_time_ms)) {
                            if (unlikely(!dm->st_util)) {
                                dm->st_util = rrdset_create_localhost("disk_util",
                                                                      disk,
                                                                      NULL,
                                                                      disk,
                                                                      "disk.util",
                                                                      "Disk Utilization Time",
                                                                      "% of time working",
                                                                      "freebsd.plugin",
                                                                      "devstat",
                                                                      NETDATA_CHART_PRIO_DISK_UTIL,
                                                                      update_every,
                                                                      RRDSET_TYPE_AREA
                                );

                                rrdset_flag_set(dm->st_util, RRDSET_FLAG_DETAIL);

                                dm->rd_util = rrddim_add(dm->st_util, "utilization", NULL, 1, 10,
                                                         RRD_ALGORITHM_INCREMENTAL);
                            } else
                                rrdset_next(dm->st_util);

                            rrddim_set_by_pointer(dm->st_util, dm->rd_util, cur_dstat.busy_time_ms);
                            rrdset_done(dm->st_util);
                        }

                        // --------------------------------------------------------------------

                        if(dm->do_iotime == CONFIG_BOOLEAN_YES || (dm->do_iotime == CONFIG_BOOLEAN_AUTO &&
                                                                   (cur_dstat.duration_read_ms ||
                                                                    cur_dstat.duration_write_ms ||
                                                                    cur_dstat.duration_other_ms ||
                                                                    cur_dstat.duration_free_ms))) {
                            if (unlikely(!dm->st_iotime)) {
                                dm->st_iotime = rrdset_create_localhost("disk_iotime",
                                                                        disk,
                                                                        NULL,
                                                                        disk,
                                                                        "disk.iotime",
                                                                        "Disk Total I/O Time",
                                                                        "milliseconds/s",
                                                                        "freebsd.plugin",
                                                                        "devstat",
                                                                        NETDATA_CHART_PRIO_DISK_IOTIME,
                                                                        update_every,
                                                                        RRDSET_TYPE_LINE
                                );

                                rrdset_flag_set(dm->st_iotime, RRDSET_FLAG_DETAIL);

                                dm->rd_iotime_in    = rrddim_add(dm->st_iotime, "reads",  NULL,  1, 1,
                                                                RRD_ALGORITHM_INCREMENTAL);
                                dm->rd_iotime_out   = rrddim_add(dm->st_iotime, "writes", NULL, -1, 1,
                                                                RRD_ALGORITHM_INCREMENTAL);
                                dm->rd_iotime_other = rrddim_add(dm->st_iotime, "other",  NULL,  1, 1,
                                                                RRD_ALGORITHM_INCREMENTAL);
                                dm->rd_iotime_free  = rrddim_add(dm->st_iotime, "frees",  NULL, -1, 1,
                                                                RRD_ALGORITHM_INCREMENTAL);
                            } else
                                rrdset_next(dm->st_iotime);

                            rrddim_set_by_pointer(dm->st_iotime, dm->rd_iotime_in,    cur_dstat.duration_read_ms);
                            rrddim_set_by_pointer(dm->st_iotime, dm->rd_iotime_out,   cur_dstat.duration_write_ms);
                            rrddim_set_by_pointer(dm->st_iotime, dm->rd_iotime_other, cur_dstat.duration_other_ms);
                            rrddim_set_by_pointer(dm->st_iotime, dm->rd_iotime_free,  cur_dstat.duration_free_ms);
                            rrdset_done(dm->st_iotime);
                        }

                        // --------------------------------------------------------------------
                        // calculate differential charts
                        // only if this is not the first time we run

                        if (likely(dt)) {

                            // --------------------------------------------------------------------

                            if(dm->do_await == CONFIG_BOOLEAN_YES || (dm->do_await == CONFIG_BOOLEAN_AUTO &&
                                                                      (dstat[i].operations[DEVSTAT_READ] ||
                                                                       dstat[i].operations[DEVSTAT_WRITE] ||
                                                                       dstat[i].operations[DEVSTAT_NO_DATA] ||
                                                                       dstat[i].operations[DEVSTAT_FREE]))) {
                                if (unlikely(!dm->st_await)) {
                                    dm->st_await = rrdset_create_localhost("disk_await",
                                                                           disk,
                                                                           NULL,
                                                                           disk,
                                                                           "disk.await",
                                                                           "Average Completed I/O Operation Time",
                                                                           "milliseconds/operation",
                                                                           "freebsd.plugin",
                                                                           "devstat",
                                                                           NETDATA_CHART_PRIO_DISK_AWAIT,
                                                                           update_every,
                                                                           RRDSET_TYPE_LINE
                                    );

                                    rrdset_flag_set(dm->st_await, RRDSET_FLAG_DETAIL);

                                    dm->rd_await_in    = rrddim_add(dm->st_await, "reads",  NULL,  1, 1,
                                                                  RRD_ALGORITHM_ABSOLUTE);
                                    dm->rd_await_out   = rrddim_add(dm->st_await, "writes", NULL, -1, 1,
                                                                  RRD_ALGORITHM_ABSOLUTE);
                                    dm->rd_await_other = rrddim_add(dm->st_await, "other",  NULL,  1, 1,
                                                                  RRD_ALGORITHM_ABSOLUTE);
                                    dm->rd_await_free  = rrddim_add(dm->st_await, "frees",  NULL, -1, 1,
                                                                  RRD_ALGORITHM_ABSOLUTE);
                                } else
                                    rrdset_next(dm->st_await);

                                rrddim_set_by_pointer(dm->st_await, dm->rd_await_in,
                                                      (dstat[i].operations[DEVSTAT_READ] -
                                                       dm->prev_dstat.operations_read) ?
                                                      (cur_dstat.duration_read_ms - dm->prev_dstat.duration_read_ms) /
                                                      (dstat[i].operations[DEVSTAT_READ] -
                                                       dm->prev_dstat.operations_read) :
                                                      0);
                                rrddim_set_by_pointer(dm->st_await, dm->rd_await_out,
                                                      (dstat[i].operations[DEVSTAT_WRITE] -
                                                       dm->prev_dstat.operations_write) ?
                                                      (cur_dstat.duration_write_ms - dm->prev_dstat.duration_write_ms) /
                                                      (dstat[i].operations[DEVSTAT_WRITE] -
                                                       dm->prev_dstat.operations_write) :
                                                      0);
                                rrddim_set_by_pointer(dm->st_await, dm->rd_await_other,
                                                      (dstat[i].operations[DEVSTAT_NO_DATA] -
                                                       dm->prev_dstat.operations_other) ?
                                                      (cur_dstat.duration_other_ms - dm->prev_dstat.duration_other_ms) /
                                                      (dstat[i].operations[DEVSTAT_NO_DATA] -
                                                       dm->prev_dstat.operations_other) :
                                                      0);
                                rrddim_set_by_pointer(dm->st_await, dm->rd_await_free,
                                                      (dstat[i].operations[DEVSTAT_FREE] -
                                                       dm->prev_dstat.operations_free) ?
                                                      (cur_dstat.duration_free_ms - dm->prev_dstat.duration_free_ms) /
                                                      (dstat[i].operations[DEVSTAT_FREE] -
                                                       dm->prev_dstat.operations_free) :
                                                      0);
                                rrdset_done(dm->st_await);
                            }

                            // --------------------------------------------------------------------

                            if(dm->do_avagsz == CONFIG_BOOLEAN_YES || (dm->do_avagsz == CONFIG_BOOLEAN_AUTO &&
                                                                       (dstat[i].operations[DEVSTAT_READ] ||
                                                                        dstat[i].operations[DEVSTAT_WRITE] ||
                                                                        dstat[i].operations[DEVSTAT_FREE]))) {
                                if (unlikely(!dm->st_avagsz)) {
                                    dm->st_avagsz = rrdset_create_localhost("disk_avgsz",
                                                                            disk,
                                                                            NULL,
                                                                            disk,
                                                                            "disk.avgsz",
                                                                            "Average Completed I/O Operation Bandwidth",
                                                                            "KiB/operation",
                                                                            "freebsd.plugin",
                                                                            "devstat",
                                                                            NETDATA_CHART_PRIO_DISK_AVGSZ,
                                                                            update_every,
                                                                            RRDSET_TYPE_AREA
                                    );

                                    rrdset_flag_set(dm->st_avagsz, RRDSET_FLAG_DETAIL);

                                    dm->rd_avagsz_in    = rrddim_add(dm->st_avagsz, "reads",  NULL,  1, KILO_FACTOR,
                                                                     RRD_ALGORITHM_ABSOLUTE);
                                    dm->rd_avagsz_out   = rrddim_add(dm->st_avagsz, "writes", NULL, -1, KILO_FACTOR,
                                                                     RRD_ALGORITHM_ABSOLUTE);
                                    dm->rd_avagsz_free  = rrddim_add(dm->st_avagsz, "frees",  NULL, -1, KILO_FACTOR,
                                                                     RRD_ALGORITHM_ABSOLUTE);
                                } else
                                    rrdset_next(dm->st_avagsz);

                                rrddim_set_by_pointer(dm->st_avagsz, dm->rd_avagsz_in,
                                                      (dstat[i].operations[DEVSTAT_READ] -
                                                       dm->prev_dstat.operations_read) ?
                                                      (dstat[i].bytes[DEVSTAT_READ] - dm->prev_dstat.bytes_read) /
                                                      (dstat[i].operations[DEVSTAT_READ] -
                                                       dm->prev_dstat.operations_read) :
                                                      0);
                                rrddim_set_by_pointer(dm->st_avagsz, dm->rd_avagsz_out,
                                                      (dstat[i].operations[DEVSTAT_WRITE] -
                                                       dm->prev_dstat.operations_write) ?
                                                      (dstat[i].bytes[DEVSTAT_WRITE] - dm->prev_dstat.bytes_write) /
                                                      (dstat[i].operations[DEVSTAT_WRITE] -
                                                       dm->prev_dstat.operations_write) :
                                                      0);
                                rrddim_set_by_pointer(dm->st_avagsz, dm->rd_avagsz_free,
                                                      (dstat[i].operations[DEVSTAT_FREE] -
                                                       dm->prev_dstat.operations_free) ?
                                                      (dstat[i].bytes[DEVSTAT_FREE] - dm->prev_dstat.bytes_free) /
                                                      (dstat[i].operations[DEVSTAT_FREE] -
                                                       dm->prev_dstat.operations_free) :
                                                      0);
                                rrdset_done(dm->st_avagsz);
                            }

                            // --------------------------------------------------------------------

                            if(dm->do_svctm == CONFIG_BOOLEAN_YES || (dm->do_svctm == CONFIG_BOOLEAN_AUTO &&
                                                                      (dstat[i].operations[DEVSTAT_READ] ||
                                                                       dstat[i].operations[DEVSTAT_WRITE] ||
                                                                       dstat[i].operations[DEVSTAT_NO_DATA] ||
                                                                       dstat[i].operations[DEVSTAT_FREE]))) {
                                if (unlikely(!dm->st_svctm)) {
                                    dm->st_svctm = rrdset_create_localhost("disk_svctm",
                                                                           disk,
                                                                           NULL,
                                                                           disk,
                                                                           "disk.svctm",
                                                                           "Average Service Time",
                                                                           "milliseconds/operation",
                                                                           "freebsd.plugin",
                                                                           "devstat",
                                                                           NETDATA_CHART_PRIO_DISK_SVCTM,
                                                                           update_every,
                                                                           RRDSET_TYPE_LINE
                                    );

                                    rrdset_flag_set(dm->st_svctm, RRDSET_FLAG_DETAIL);

                                    dm->rd_svctm = rrddim_add(dm->st_svctm, "svctm", NULL, 1, 1,
                                                              RRD_ALGORITHM_ABSOLUTE);
                                } else
                                    rrdset_next(dm->st_svctm);

                                rrddim_set_by_pointer(dm->st_svctm, dm->rd_svctm,
                                                      ((dstat[i].operations[DEVSTAT_READ] - dm->prev_dstat.operations_read) +
                                                       (dstat[i].operations[DEVSTAT_WRITE] - dm->prev_dstat.operations_write) +
                                                       (dstat[i].operations[DEVSTAT_NO_DATA] - dm->prev_dstat.operations_other) +
                                                       (dstat[i].operations[DEVSTAT_FREE] - dm->prev_dstat.operations_free)) ?
                                                      (cur_dstat.busy_time_ms - dm->prev_dstat.busy_time_ms) /
                                                      ((dstat[i].operations[DEVSTAT_READ] - dm->prev_dstat.operations_read) +
                                                       (dstat[i].operations[DEVSTAT_WRITE] - dm->prev_dstat.operations_write) +
                                                       (dstat[i].operations[DEVSTAT_NO_DATA] - dm->prev_dstat.operations_other) +
                                                       (dstat[i].operations[DEVSTAT_FREE] - dm->prev_dstat.operations_free)) :
                                                      0);
                                rrdset_done(dm->st_svctm);
                            }

                            // --------------------------------------------------------------------

                            dm->prev_dstat.bytes_read        = dstat[i].bytes[DEVSTAT_READ];
                            dm->prev_dstat.bytes_write       = dstat[i].bytes[DEVSTAT_WRITE];
                            dm->prev_dstat.bytes_free        = dstat[i].bytes[DEVSTAT_FREE];
                            dm->prev_dstat.operations_read   = dstat[i].operations[DEVSTAT_READ];
                            dm->prev_dstat.operations_write  = dstat[i].operations[DEVSTAT_WRITE];
                            dm->prev_dstat.operations_other  = dstat[i].operations[DEVSTAT_NO_DATA];
                            dm->prev_dstat.operations_free   = dstat[i].operations[DEVSTAT_FREE];
                            dm->prev_dstat.duration_read_ms  = cur_dstat.duration_read_ms;
                            dm->prev_dstat.duration_write_ms = cur_dstat.duration_write_ms;
                            dm->prev_dstat.duration_other_ms = cur_dstat.duration_other_ms;
                            dm->prev_dstat.duration_free_ms  = cur_dstat.duration_free_ms;
                            dm->prev_dstat.busy_time_ms      = cur_dstat.busy_time_ms;
                        }
                    }
                }

                // --------------------------------------------------------------------

                if (likely(do_system_io)) {
                    static RRDSET *st = NULL;
                    static RRDDIM *rd_in = NULL, *rd_out = NULL;

                    if (unlikely(!st)) {
                        st = rrdset_create_localhost("system",
                                                     "io",
                                                     NULL,
                                                     "disk",
                                                     NULL,
                                                     "Disk I/O",
                                                     "KiB/s",
                                                     "freebsd.plugin",
                                                     "devstat",
                                                     NETDATA_CHART_PRIO_SYSTEM_IO,
                                                     update_every,
                                                     RRDSET_TYPE_AREA
                        );

                        rd_in  = rrddim_add(st, "in",  NULL,  1, 1, RRD_ALGORITHM_INCREMENTAL);
                        rd_out = rrddim_add(st, "out", NULL, -1, 1, RRD_ALGORITHM_INCREMENTAL);
                    } else
                        rrdset_next(st);

                    rrddim_set_by_pointer(st, rd_in,  total_disk_kbytes_read);
                    rrddim_set_by_pointer(st, rd_out, total_disk_kbytes_write);
                    rrdset_done(st);
                }
            }
        }
        if (unlikely(common_error)) {
            do_system_io = 0;
            error("DISABLED: system.io chart");
            do_io = 0;
            error("DISABLED: disk.* charts");
            do_ops = 0;
            error("DISABLED: disk_ops.* charts");
            do_qops = 0;
            error("DISABLED: disk_qops.* charts");
            do_util = 0;
            error("DISABLED: disk_util.* charts");
            do_iotime = 0;
            error("DISABLED: disk_iotime.* charts");
            do_await = 0;
            error("DISABLED: disk_await.* charts");
            do_avagsz = 0;
            error("DISABLED: disk_avgsz.* charts");
            do_svctm = 0;
            error("DISABLED: disk_svctm.* charts");
            error("DISABLED: kern.devstat module");
            return 1;
        }
    } else {
        error("DISABLED: kern.devstat module");
        return 1;
    }

    disks_cleanup();

    return 0;
}