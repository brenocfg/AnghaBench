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

/* Variables and functions */
 int /*<<< orphan*/  D_RRDHOST ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fatal (char*,char const*,unsigned long const,char const*) ; 
 int netdata_rwlock_tryrdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrd_rwlock ; 

void __rrd_check_wrlock(const char *file, const char *function, const unsigned long line) {
    debug(D_RRDHOST, "Checking write lock on all RRDs");

    int ret = netdata_rwlock_tryrdlock(&rrd_rwlock);
    if(ret == 0)
        fatal("RRDs should be write-locked, but it are not, at function %s() at line %lu of file '%s'", function, line, file);
}