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
 int DDRF ; 
 int PORTF ; 

__attribute__((used)) static void init_cols(void) {
  // init on mcp23018
  // not needed, already done as part of init_mcp23018()

  // init on teensy
  // Input with pull-up(DDR:0, PORT:1)
  DDRF &= ~(1 << 7 | 1 << 6 | 1 << 5 | 1 << 4 | 1 << 1 | 1 << 0);
  PORTF |= (1 << 7 | 1 << 6 | 1 << 5 | 1 << 4 | 1 << 1 | 1 << 0);
}