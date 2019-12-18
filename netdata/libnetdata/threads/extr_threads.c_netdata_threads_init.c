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
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_OPTIONS ; 
 int /*<<< orphan*/  attr ; 
 int /*<<< orphan*/  callocz (int,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t default_stacksize ; 
 int /*<<< orphan*/  fatal (char*,int) ; 
 int pthread_attr_getstacksize (int /*<<< orphan*/ ,size_t*) ; 
 int pthread_attr_init (int /*<<< orphan*/ ) ; 

size_t netdata_threads_init(void) {
    int i;

    // --------------------------------------------------------------------
    // get the required stack size of the threads of netdata

    attr = callocz(1, sizeof(pthread_attr_t));
    i = pthread_attr_init(attr);
    if(i != 0)
        fatal("pthread_attr_init() failed with code %d.", i);

    i = pthread_attr_getstacksize(attr, &default_stacksize);
    if(i != 0)
        fatal("pthread_attr_getstacksize() failed with code %d.", i);
    else
        debug(D_OPTIONS, "initial pthread stack size is %zu bytes", default_stacksize);

    return default_stacksize;
}