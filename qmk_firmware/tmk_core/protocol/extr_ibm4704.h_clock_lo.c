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
 int IBM4704_CLOCK_BIT ; 
 int IBM4704_CLOCK_DDR ; 
 int IBM4704_CLOCK_PORT ; 

__attribute__((used)) static inline void clock_lo(void) {
    IBM4704_CLOCK_PORT &= ~(1 << IBM4704_CLOCK_BIT);
    IBM4704_CLOCK_DDR |= (1 << IBM4704_CLOCK_BIT);
}