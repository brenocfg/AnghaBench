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
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  lwan_status_warning (char*) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned short int get_number_of_cpus(void)
{
    long n_online_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    if (UNLIKELY(n_online_cpus < 0)) {
        lwan_status_warning(
            "Could not get number of online CPUs, assuming 1 CPU");
        return 1;
    }
    return (unsigned short int)n_online_cpus;
}