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
 int pthread_cancel (int /*<<< orphan*/ ) ; 

int netdata_thread_cancel(netdata_thread_t thread) {
    int ret = pthread_cancel(thread);
    if(ret != 0)
        error("cannot cancel thread. pthread_cancel() failed with code %d.", ret);

    return ret;
}