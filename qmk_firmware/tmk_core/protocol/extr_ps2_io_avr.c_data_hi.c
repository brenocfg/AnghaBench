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
 int PS2_DATA_BIT ; 
 int PS2_DATA_DDR ; 
 int PS2_DATA_PORT ; 

void data_hi(void) {
    /* input with pull up */
    PS2_DATA_DDR &= ~(1 << PS2_DATA_BIT);
    PS2_DATA_PORT |= (1 << PS2_DATA_BIT);
}