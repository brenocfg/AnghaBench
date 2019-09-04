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
typedef  int /*<<< orphan*/  netdata_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  netdata_thread_disable_cancelability () ; 
 int /*<<< orphan*/  netdata_thread_enable_cancelability () ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int __netdata_mutex_lock(netdata_mutex_t *mutex) {
    netdata_thread_disable_cancelability();

    int ret = pthread_mutex_lock(mutex);
    if(unlikely(ret != 0)) {
        netdata_thread_enable_cancelability();
        error("MUTEX_LOCK: failed to get lock (code %d)", ret);
    }
    return ret;
}