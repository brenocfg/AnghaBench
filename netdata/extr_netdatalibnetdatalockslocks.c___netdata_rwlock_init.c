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
 int pthread_rwlock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int __netdata_rwlock_init(netdata_rwlock_t *rwlock) {
    int ret = pthread_rwlock_init(rwlock, NULL);
    if(unlikely(ret != 0))
        error("RW_LOCK: failed to initialize lock (code %d)", ret);
    return ret;
}