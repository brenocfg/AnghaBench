#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int OSPEEDR; scalar_t__* AFR; scalar_t__ PUPDR; scalar_t__ ODR; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN1 ; 
 int /*<<< orphan*/  CAN2 ; 
 TYPE_1__* GPIOA ; 
 TYPE_1__* GPIOB ; 
 TYPE_1__* GPIOC ; 
 int /*<<< orphan*/  GPIO_AF10_OTG_FS ; 
 int /*<<< orphan*/  GPIO_AF2_TIM3 ; 
 int /*<<< orphan*/  GPIO_AF9_CAN1 ; 
 int GPIO_OSPEEDER_OSPEEDR11 ; 
 int GPIO_OSPEEDER_OSPEEDR12 ; 
 int /*<<< orphan*/  LED_BLUE ; 
 int /*<<< orphan*/  LED_GREEN ; 
 int /*<<< orphan*/  LED_RED ; 
 int /*<<< orphan*/  MODE_ANALOG ; 
 scalar_t__ PANDA_REV_C ; 
 int /*<<< orphan*/  USB_POWER_CLIENT ; 
 scalar_t__ revision ; 
 int /*<<< orphan*/  set_can_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_can_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_alternate (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_mode (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gpio_output (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  set_led (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_usb_power_mode (int /*<<< orphan*/ ) ; 

void gpio_init() {
  // pull low to hold ESP in reset??
  // enable OTG out tied to ground
  GPIOA->ODR = 0;
  GPIOB->ODR = 0;
  GPIOA->PUPDR = 0;
  //GPIOC->ODR = 0;
  GPIOB->AFR[0] = 0;
  GPIOB->AFR[1] = 0;

  // C2,C3: analog mode, voltage and current sense
  set_gpio_mode(GPIOC, 2, MODE_ANALOG);
  set_gpio_mode(GPIOC, 3, MODE_ANALOG);

#ifdef PEDAL
  // comma pedal has inputs on C0 and C1
  set_gpio_mode(GPIOC, 0, MODE_ANALOG);
  set_gpio_mode(GPIOC, 1, MODE_ANALOG);
  // DAC outputs on A4 and A5
  //   apparently they don't need GPIO setup
#endif

  // C8: FAN aka TIM3_CH4
  set_gpio_alternate(GPIOC, 8, GPIO_AF2_TIM3);

  // turn off LEDs and set mode
  set_led(LED_RED, 0);
  set_led(LED_GREEN, 0);
  set_led(LED_BLUE, 0);

  // A11,A12: USB
  set_gpio_alternate(GPIOA, 11, GPIO_AF10_OTG_FS);
  set_gpio_alternate(GPIOA, 12, GPIO_AF10_OTG_FS);
  GPIOA->OSPEEDR = GPIO_OSPEEDER_OSPEEDR11 | GPIO_OSPEEDER_OSPEEDR12;

#ifdef PANDA
  // enable started_alt on the panda
  set_gpio_pullup(GPIOA, 1, PULL_UP);

  // A2,A3: USART 2 for debugging
  set_gpio_alternate(GPIOA, 2, GPIO_AF7_USART2);
  set_gpio_alternate(GPIOA, 3, GPIO_AF7_USART2);

  // A9,A10: USART 1 for talking to the ESP
  set_gpio_alternate(GPIOA, 9, GPIO_AF7_USART1);
  set_gpio_alternate(GPIOA, 10, GPIO_AF7_USART1);

  // B12: GMLAN, ignition sense, pull up
  set_gpio_pullup(GPIOB, 12, PULL_UP);

  // A4,A5,A6,A7: setup SPI
  set_gpio_alternate(GPIOA, 4, GPIO_AF5_SPI1);
  set_gpio_alternate(GPIOA, 5, GPIO_AF5_SPI1);
  set_gpio_alternate(GPIOA, 6, GPIO_AF5_SPI1);
  set_gpio_alternate(GPIOA, 7, GPIO_AF5_SPI1);
#endif

  // B8,B9: CAN 1
#ifdef STM32F4
  set_gpio_alternate(GPIOB, 8, GPIO_AF8_CAN1);
  set_gpio_alternate(GPIOB, 9, GPIO_AF8_CAN1);
#else
  set_gpio_alternate(GPIOB, 8, GPIO_AF9_CAN1);
  set_gpio_alternate(GPIOB, 9, GPIO_AF9_CAN1);
#endif
  set_can_enable(CAN1, 1);

  // B5,B6: CAN 2
  set_can_mode(1, 0);
  set_can_enable(CAN2, 1);

  // A8,A15: CAN 3
  #ifdef CAN3
    set_can_mode(2, 0);
    set_can_enable(CAN3, 1);
  #endif

  /* GMLAN mode pins:
  M0(B15)  M1(B14)  mode
  =======================
  0        0        sleep
  1        0        100kbit
  0        1        high voltage wakeup
  1        1        33kbit (normal)
  */

  // put gmlan transceiver in normal mode
  set_gpio_output(GPIOB, 14, 1);
  set_gpio_output(GPIOB, 15, 1);

  #ifdef PANDA
    // K-line enable moved from B4->B7 to make room for GMLAN on CAN3
    if (revision == PANDA_REV_C) {
      set_gpio_output(GPIOB, 7, 1); // REV C
    } else {
      set_gpio_output(GPIOB, 4, 1); // REV AB
    }

    // C12,D2: K-Line setup on UART 5
    set_gpio_alternate(GPIOC, 12, GPIO_AF8_UART5);
    set_gpio_alternate(GPIOD, 2, GPIO_AF8_UART5);
    set_gpio_pullup(GPIOD, 2, PULL_UP);

    // L-line enable
    set_gpio_output(GPIOA, 14, 1);

    // C10,C11: L-Line setup on USART 3
    // LLine now used for relay output
    set_gpio_output(GPIOC, 10, 1);
    //set_gpio_alternate(GPIOC, 10, GPIO_AF7_USART3);
    set_gpio_alternate(GPIOC, 11, GPIO_AF7_USART3);
    set_gpio_pullup(GPIOC, 11, PULL_UP);
  #endif

  if (revision == PANDA_REV_C) {
    set_usb_power_mode(USB_POWER_CLIENT);
  }
}