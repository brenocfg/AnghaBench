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
 int /*<<< orphan*/  GPIO_ID_PIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_PIN_ADDR (int /*<<< orphan*/ ) ; 
 int GPIO_PIN_SOURCE_MASK ; 
 int GPIO_PIN_SOURCE_SET (int /*<<< orphan*/ ) ; 
 int GPIO_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int NUM_GPIO ; 
 int /*<<< orphan*/  PLATFORM_GPIO_FLOAT ; 
 int /*<<< orphan*/  PLATFORM_GPIO_LOW ; 
 int /*<<< orphan*/  PLATFORM_GPIO_OUTPUT ; 
 int /*<<< orphan*/  SIGMA_AS_PIN_SOURCE ; 
 int /*<<< orphan*/ * pin_num ; 
 int /*<<< orphan*/  platform_gpio_mode (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_gpio_write (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigma_delta_setup () ; 

uint8_t platform_sigma_delta_setup( uint8_t pin )
{
  if (pin < 1 || pin > NUM_GPIO)
    return 0;

  sigma_delta_setup();

  // set GPIO output mode for this pin
  platform_gpio_mode( pin, PLATFORM_GPIO_OUTPUT, PLATFORM_GPIO_FLOAT );
  platform_gpio_write( pin, PLATFORM_GPIO_LOW );

  // enable sigma-delta on this pin
  GPIO_REG_WRITE(GPIO_PIN_ADDR(GPIO_ID_PIN(pin_num[pin])),
                 (GPIO_REG_READ(GPIO_PIN_ADDR(GPIO_ID_PIN(pin_num[pin]))) &(~GPIO_PIN_SOURCE_MASK)) |
                 GPIO_PIN_SOURCE_SET( SIGMA_AS_PIN_SOURCE ));

  return 1;
}