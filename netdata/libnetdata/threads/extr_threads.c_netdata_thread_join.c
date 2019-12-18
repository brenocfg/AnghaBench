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
typedef  int /*<<< orphan*/  netdata_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 

int netdata_thread_join(netdata_thread_t thread, void **retval) {
    int ret = pthread_join(thread, retval);
    if(ret != 0)
        error("cannot join thread. pthread_join() failed with code %d.", ret);

    return ret;
}