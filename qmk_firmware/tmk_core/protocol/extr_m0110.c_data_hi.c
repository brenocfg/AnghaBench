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
 int M0110_DATA_BIT ; 
 int M0110_DATA_DDR ; 
 int M0110_DATA_PORT ; 

__attribute__((used)) static inline void data_hi() {
    /* input with pull up */
    M0110_DATA_DDR &= ~(1 << M0110_DATA_BIT);
    M0110_DATA_PORT |= (1 << M0110_DATA_BIT);
}