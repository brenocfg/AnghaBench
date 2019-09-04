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
typedef  int /*<<< orphan*/  procfile ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  FILENAME_MAX ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_ENTROPY ; 
 int /*<<< orphan*/  PLUGIN_PROC_NAME ; 
 int /*<<< orphan*/  PROCFILE_FLAG_DEFAULT ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  config_get (char*,char*,char*) ; 
 int /*<<< orphan*/  netdata_configured_host_prefix ; 
 int /*<<< orphan*/  procfile_lineword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * procfile_readall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 unsigned long long str2ull (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int do_proc_sys_kernel_random_entropy_avail(int update_every, usec_t dt) {
    (void)dt;

    static procfile *ff = NULL;

    if(unlikely(!ff)) {
        char filename[FILENAME_MAX + 1];
        snprintfz(filename, FILENAME_MAX, "%s%s", netdata_configured_host_prefix, "/proc/sys/kernel/random/entropy_avail");
        ff = procfile_open(config_get("plugin:proc:/proc/sys/kernel/random/entropy_avail", "filename to monitor", filename), "", PROCFILE_FLAG_DEFAULT);
        if(unlikely(!ff)) return 1;
    }

    ff = procfile_readall(ff);
    if(unlikely(!ff)) return 0; // we return 0, so that we will retry to open it next time

    unsigned long long entropy = str2ull(procfile_lineword(ff, 0, 0));

    static RRDSET *st = NULL;
    static RRDDIM *rd = NULL;

    if(unlikely(!st)) {
        st = rrdset_create_localhost(
                "system"
                , "entropy"
                , NULL
                , "entropy"
                , NULL
                , "Available Entropy"
                , "entropy"
                , PLUGIN_PROC_NAME
                , "/proc/sys/kernel/random/entropy_avail"
                , NETDATA_CHART_PRIO_SYSTEM_ENTROPY
                , update_every
                , RRDSET_TYPE_LINE
        );

        rd = rrddim_add(st, "entropy", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
    }
    else rrdset_next(st);

    rrddim_set_by_pointer(st, rd, entropy);
    rrdset_done(st);

    return 0;
}