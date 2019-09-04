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
typedef  int /*<<< orphan*/  netdata_mutex_t ;

/* Variables and functions */
 int D_LOCKS ; 
 int __netdata_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ *,unsigned long const,...) ; 
 int debug_flags ; 
 int /*<<< orphan*/  now_boottime_usec () ; 
 scalar_t__ unlikely (int) ; 

int netdata_mutex_lock_debug( const char *file, const char *function, const unsigned long line, netdata_mutex_t *mutex) {
    usec_t start = 0;
    (void)start;

    if(unlikely(debug_flags & D_LOCKS)) {
        start = now_boottime_usec();
        debug(D_LOCKS, "MUTEX_LOCK: netdata_mutex_lock(0x%p) from %lu@%s, %s()", mutex, line, file, function);
    }

    int ret = __netdata_mutex_lock(mutex);

    debug(D_LOCKS, "MUTEX_LOCK: netdata_mutex_lock(0x%p) = %d in %llu usec, from %lu@%s, %s()", mutex, ret, now_boottime_usec() - start, line, file, function);

    return ret;
}