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
typedef  int uint8_t ;

/* Variables and functions */
 int PORTB ; 

__attribute__((used)) static inline void SET_COL(uint8_t COL)
{
    // PB0-3
    PORTB = (PORTB & 0xF0) | (COL & 0x0F);
}