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
 int /*<<< orphan*/  BOARD_LED_BLUE_GPIO_PIN ; 
 int /*<<< orphan*/  BOARD_LED_BLUE_GPIO_PORT ; 
 int /*<<< orphan*/  BOARD_LED_GREEN_GPIO_PIN ; 
 int /*<<< orphan*/  BOARD_LED_GREEN_GPIO_PORT ; 
 int /*<<< orphan*/  BOARD_LED_RED_GPIO_PIN ; 
 int /*<<< orphan*/  BOARD_LED_RED_GPIO_PORT ; 
 int /*<<< orphan*/  CLOCK_EnableClock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_BLUE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_BLUE_OFF () ; 
 int /*<<< orphan*/  LED_GREEN_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_RED_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_SetPinMux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCLOCK_PortA ; 
 int /*<<< orphan*/  kCLOCK_PortB ; 
 int /*<<< orphan*/  kCLOCK_PortE ; 
 int /*<<< orphan*/  kPORT_MuxAsGpio ; 

void gpio_init() {
  CLOCK_EnableClock(kCLOCK_PortA);
  CLOCK_EnableClock(kCLOCK_PortB);
  CLOCK_EnableClock(kCLOCK_PortE);
  PORT_SetPinMux(BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_GPIO_PIN,
                 kPORT_MuxAsGpio);
  LED_RED_INIT(0);
  PORT_SetPinMux(BOARD_LED_GREEN_GPIO_PORT, BOARD_LED_GREEN_GPIO_PIN,
                 kPORT_MuxAsGpio);
  LED_GREEN_INIT(0);
  PORT_SetPinMux(BOARD_LED_BLUE_GPIO_PORT, BOARD_LED_BLUE_GPIO_PIN,
                 kPORT_MuxAsGpio);
  LED_BLUE_INIT(0);
  LED_BLUE_OFF();
}