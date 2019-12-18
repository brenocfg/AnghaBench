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
 int GETSYSCTL_BY_NAME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ getpagesize () ; 
 int /*<<< orphan*/  number_of_cpus ; 
 scalar_t__ system_pagesize ; 
 scalar_t__ unlikely (int) ; 

int freebsd_plugin_init()
{
    system_pagesize = getpagesize();
    if (system_pagesize <= 0) {
        error("FREEBSD: can't get system page size");
        return 1;
    }

    if (unlikely(GETSYSCTL_BY_NAME("kern.smp.cpus", number_of_cpus))) {
        error("FREEBSD: can't get number of cpus");
        return 1;
    }

    if (unlikely(!number_of_cpus)) {
        error("FREEBSD: wrong number of cpus");
        return 1;
    }

    return 0;
}