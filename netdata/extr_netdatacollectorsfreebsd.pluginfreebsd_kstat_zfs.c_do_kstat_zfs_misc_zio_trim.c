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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 scalar_t__ GETSYSCTL_SIMPLE (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_kstat_zfs_misc_zio_trim(int update_every, usec_t dt) {
    (void)dt;
    static int mib_bytes[5] = {0, 0, 0, 0, 0}, mib_success[5] = {0, 0, 0, 0, 0},
               mib_failed[5] = {0, 0, 0, 0, 0}, mib_unsupported[5] = {0, 0, 0, 0, 0};
    uint64_t bytes, success, failed, unsupported;

    if (unlikely(GETSYSCTL_SIMPLE("kstat.zfs.misc.zio_trim.bytes", mib_bytes, bytes) ||
                 GETSYSCTL_SIMPLE("kstat.zfs.misc.zio_trim.success", mib_success, success) ||
                 GETSYSCTL_SIMPLE("kstat.zfs.misc.zio_trim.failed", mib_failed, failed) ||
                 GETSYSCTL_SIMPLE("kstat.zfs.misc.zio_trim.unsupported", mib_unsupported, unsupported))) {
        error("DISABLED: zfs.trim_bytes chart");
        error("DISABLED: zfs.trim_success chart");
        error("DISABLED: kstat.zfs.misc.zio_trim module");
        return 1;
     } else {

     // --------------------------------------------------------------------

        static RRDSET *st_bytes = NULL;
        static RRDDIM *rd_bytes = NULL;

        if (unlikely(!st_bytes)) {
            st_bytes = rrdset_create_localhost(
                    "zfs",
                    "trim_bytes",
                    NULL,
                    "trim",
                    NULL,
                    "Successfully TRIMmed bytes",
                    "bytes",
                    "freebsd",
                    "zfs",
                    2320,
                    update_every,
                    RRDSET_TYPE_LINE
            );

            rd_bytes = rrddim_add(st_bytes, "TRIMmed", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
        }
        else rrdset_next(st_bytes);

        rrddim_set_by_pointer(st_bytes, rd_bytes, bytes);
        rrdset_done(st_bytes);

        // --------------------------------------------------------------------

        static RRDSET *st_requests = NULL;
        static RRDDIM *rd_successful = NULL, *rd_failed = NULL, *rd_unsupported = NULL;

        if (unlikely(!st_requests)) {
            st_requests = rrdset_create_localhost(
                    "zfs",
                    "trim_requests",
                    NULL,
                    "trim",
                    NULL,
                    "TRIM requests",
                    "requests",
                    "freebsd",
                    "zfs",
                    2321,
                    update_every,
                    RRDSET_TYPE_STACKED
            );

            rd_successful  = rrddim_add(st_requests, "successful",  NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
            rd_failed      = rrddim_add(st_requests, "failed",      NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
            rd_unsupported = rrddim_add(st_requests, "unsupported", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
        }
        else rrdset_next(st_requests);

        rrddim_set_by_pointer(st_requests, rd_successful,  success);
        rrddim_set_by_pointer(st_requests, rd_failed,      failed);
        rrddim_set_by_pointer(st_requests, rd_unsupported, unsupported);
        rrdset_done(st_requests);

     }

    return 0;
}