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
 int /*<<< orphan*/  netdata_thread_disable_cancelability () ; 
 int /*<<< orphan*/  netdata_thread_enable_cancelability () ; 
 int pthread_rwlock_tryrdlock (int /*<<< orphan*/ *) ; 

int __netdata_rwlock_tryrdlock(netdata_rwlock_t *rwlock) {
    netdata_thread_disable_cancelability();

    int ret = pthread_rwlock_tryrdlock(rwlock);
    if(ret != 0)
        netdata_thread_enable_cancelability();

    return ret;
}