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
 int /*<<< orphan*/  _SC_CLK_TCK ; 
 int /*<<< orphan*/  error (char*) ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 unsigned int system_hz ; 

void get_system_HZ(void) {
    long ticks;

    if ((ticks = sysconf(_SC_CLK_TCK)) == -1) {
        error("Cannot get system clock ticks");
    }

    system_hz = (unsigned int) ticks;
}