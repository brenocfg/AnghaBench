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
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ sint16 ;

/* Variables and functions */

__attribute__((used)) static inline void i2c_master_wait_cpu_cycles(sint16 cycles_delay)
{
    uint32 cycles_start;
    uint32 cycles_curr;
    // uses special 'ccount' register which is increased every CPU cycle
    // to make precise delay
    asm volatile("rsr %0, ccount":"=a"(cycles_start));
    do{
        asm volatile("rsr %0, ccount":"=a"(cycles_curr));
    } while (cycles_curr - cycles_start <  cycles_delay);
}