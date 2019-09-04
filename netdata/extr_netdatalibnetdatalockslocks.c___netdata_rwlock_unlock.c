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
typedef  int /*<<< orphan*/  netdata_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  netdata_thread_enable_cancelability () ; 
 int pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int __netdata_rwlock_unlock(netdata_rwlock_t *rwlock) {
    int ret = pthread_rwlock_unlock(rwlock);
    if(unlikely(ret != 0))
        error("RW_LOCK: failed to release lock (code %d)", ret);
    else
        netdata_thread_enable_cancelability();

    return ret;
}