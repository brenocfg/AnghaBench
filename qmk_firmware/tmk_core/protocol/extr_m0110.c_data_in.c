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
 int M0110_DATA_PIN ; 
 int M0110_DATA_PORT ; 
 int /*<<< orphan*/  _delay_us (int) ; 

__attribute__((used)) static inline bool data_in() {
    M0110_DATA_DDR &= ~(1 << M0110_DATA_BIT);
    M0110_DATA_PORT |= (1 << M0110_DATA_BIT);
    _delay_us(1);
    return M0110_DATA_PIN & (1 << M0110_DATA_BIT);
}