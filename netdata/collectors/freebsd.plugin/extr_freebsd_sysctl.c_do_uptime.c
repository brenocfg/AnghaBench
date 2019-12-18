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
struct timespec {int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_UPTIME ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_SYSTEM_UPTIME ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int do_uptime(int update_every, usec_t dt) {
    (void)dt;
    struct timespec up_time;

    clock_gettime(CLOCK_UPTIME, &up_time);

    // --------------------------------------------------------------------

    static RRDSET *st = NULL;
    static RRDDIM *rd = NULL;

    if(unlikely(!st)) {
        st = rrdset_create_localhost(
                "system",
                "uptime",
                NULL,
                "uptime",
                NULL,
                "System Uptime",
                "seconds",
                "freebsd.plugin",
                "uptime",
                NETDATA_CHART_PRIO_SYSTEM_UPTIME,
                update_every,
                RRDSET_TYPE_LINE
        );

        rd = rrddim_add(st, "uptime", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
    }
    else rrdset_next(st);

    rrddim_set_by_pointer(st, rd, up_time.tv_sec);
    rrdset_done(st);

    return 0;
}