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
 int /*<<< orphan*/  BSP_LED_Toggle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Delay (int) ; 
 int /*<<< orphan*/  LED4 ; 

void Error_Handler() {
  /* Turn LED4 (red) on/off */
  while (1) {
    BSP_LED_Toggle(LED4);
    Delay(100);
  }
}