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
 int /*<<< orphan*/  D_SYSTEM ; 
 scalar_t__ attr ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t default_stacksize ; 
 int /*<<< orphan*/  fatal (char*,size_t,int) ; 
 int pthread_attr_setstacksize (scalar_t__,size_t) ; 
 size_t wanted_stacksize ; 

void netdata_threads_init_after_fork(size_t stacksize) {
    wanted_stacksize = stacksize;
    int i;

    // ------------------------------------------------------------------------
    // set default pthread stack size

    if(attr && default_stacksize < wanted_stacksize && wanted_stacksize > 0) {
        i = pthread_attr_setstacksize(attr, wanted_stacksize);
        if(i != 0)
            fatal("pthread_attr_setstacksize() to %zu bytes, failed with code %d.", wanted_stacksize, i);
        else
            debug(D_SYSTEM, "Successfully set pthread stacksize to %zu bytes", wanted_stacksize);
    }
}