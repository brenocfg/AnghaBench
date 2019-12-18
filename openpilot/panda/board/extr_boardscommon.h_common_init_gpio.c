#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int OSPEEDR; scalar_t__* AFR; scalar_t__ PUPDR; scalar_t__ ODR; } ;

/* Variables and functions */
 TYPE_1__* GPIOA ; 
 TYPE_1__* GPIOB ; 
 int /*<<< orphan*/  GPIOC ; 
 int /*<<< orphan*/  GPIO_AF10_OTG_FS ; 
 int /*<<< orphan*/  GPIO_AF7_USART1 ; 
 int /*<<< orphan*/  GPIO_AF8_CAN1 ; 
 int /*<<< orphan*/  GPIO_AF9_CAN1 ; 
 int GPIO_OSPEEDER_OSPEEDR11 ; 
 int GPIO_OSPEEDER_OSPEEDR12 ; 
 int /*<<< orphan*/  MODE_ANALOG ; 
 int /*<<< orphan*/  set_gpio_alternate (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_mode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void common_init_gpio(void){
  // TODO: Is this block actually doing something???
  // pull low to hold ESP in reset??
  // enable OTG out tied to ground
  GPIOA->ODR = 0;
  GPIOB->ODR = 0;
  GPIOA->PUPDR = 0;
  GPIOB->AFR[0] = 0;
  GPIOB->AFR[1] = 0;

  // C2: Voltage sense line
  set_gpio_mode(GPIOC, 2, MODE_ANALOG);

  // A11,A12: USB
  set_gpio_alternate(GPIOA, 11, GPIO_AF10_OTG_FS);
  set_gpio_alternate(GPIOA, 12, GPIO_AF10_OTG_FS);
  GPIOA->OSPEEDR = GPIO_OSPEEDER_OSPEEDR11 | GPIO_OSPEEDER_OSPEEDR12;

  // A9,A10: USART 1 for talking to the ESP / GPS
  set_gpio_alternate(GPIOA, 9, GPIO_AF7_USART1);
  set_gpio_alternate(GPIOA, 10, GPIO_AF7_USART1);

   // B8,B9: CAN 1
  #ifdef STM32F4
    set_gpio_alternate(GPIOB, 8, GPIO_AF8_CAN1);
    set_gpio_alternate(GPIOB, 9, GPIO_AF8_CAN1);
  #else
    set_gpio_alternate(GPIOB, 8, GPIO_AF9_CAN1);
    set_gpio_alternate(GPIOB, 9, GPIO_AF9_CAN1);
  #endif
}