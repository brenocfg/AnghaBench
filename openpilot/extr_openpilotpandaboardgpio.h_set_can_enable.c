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
typedef  int /*<<< orphan*/  CAN_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/ * CAN1 ; 
 int /*<<< orphan*/ * CAN2 ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  set_gpio_output (int /*<<< orphan*/ ,int,int) ; 

void set_can_enable(CAN_TypeDef *CAN, int enabled) {
  // enable CAN busses
  if (CAN == CAN1) {
    #ifdef PANDA
      // CAN1_EN
      set_gpio_output(GPIOC, 1, !enabled);
    #else
      #ifdef PEDAL
        // CAN1_EN (not flipped)
        set_gpio_output(GPIOB, 3, !enabled);
      #else
        // CAN1_EN
        set_gpio_output(GPIOB, 3, enabled);
      #endif
    #endif
  } else if (CAN == CAN2) {
    #ifdef PANDA
      // CAN2_EN
      set_gpio_output(GPIOC, 13, !enabled);
    #else
      // CAN2_EN
      set_gpio_output(GPIOB, 4, enabled);
    #endif
  #ifdef CAN3
  } else if (CAN == CAN3) {
    // CAN3_EN
    set_gpio_output(GPIOA, 0, !enabled);
  #endif
  }
}