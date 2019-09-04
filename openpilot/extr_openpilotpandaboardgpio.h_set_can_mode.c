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
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  GPIO_AF9_CAN2 ; 
 int /*<<< orphan*/  MODE_INPUT ; 
 int /*<<< orphan*/  set_gpio_alternate (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_mode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void set_can_mode(int can, int use_gmlan) {
  // connects to CAN2 xcvr or GMLAN xcvr
  if (use_gmlan) {
    if (can == 1) {
      // B5,B6: disable normal mode
      set_gpio_mode(GPIOB, 5, MODE_INPUT);
      set_gpio_mode(GPIOB, 6, MODE_INPUT);

      // B12,B13: gmlan mode
      set_gpio_alternate(GPIOB, 12, GPIO_AF9_CAN2);
      set_gpio_alternate(GPIOB, 13, GPIO_AF9_CAN2);
#ifdef CAN3
    } else if (revision == PANDA_REV_C && can == 2) {
      // A8,A15: disable normal mode
      set_gpio_mode(GPIOA, 8, MODE_INPUT);
      set_gpio_mode(GPIOA, 15, MODE_INPUT);

      // B3,B4: enable gmlan mode
      set_gpio_alternate(GPIOB, 3, GPIO_AF11_CAN3);
      set_gpio_alternate(GPIOB, 4, GPIO_AF11_CAN3);
#endif
    }
  } else {
    if (can == 1) {
      // B12,B13: disable gmlan mode
      set_gpio_mode(GPIOB, 12, MODE_INPUT);
      set_gpio_mode(GPIOB, 13, MODE_INPUT);

      // B5,B6: normal mode
      set_gpio_alternate(GPIOB, 5, GPIO_AF9_CAN2);
      set_gpio_alternate(GPIOB, 6, GPIO_AF9_CAN2);
#ifdef CAN3
    } else if (can == 2) {
      if(revision == PANDA_REV_C){
        // B3,B4: disable gmlan mode
        set_gpio_mode(GPIOB, 3, MODE_INPUT);
        set_gpio_mode(GPIOB, 4, MODE_INPUT);
      }
      // A8,A15: normal mode
      set_gpio_alternate(GPIOA, 8, GPIO_AF11_CAN3);
      set_gpio_alternate(GPIOA, 15, GPIO_AF11_CAN3);
#endif
    }
  }
}