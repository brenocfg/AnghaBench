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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 unsigned int NUM_PWM ; 
 int /*<<< orphan*/  PLATFORM_GPIO_FLOAT ; 
 int /*<<< orphan*/  PLATFORM_GPIO_OUTPUT ; 
 int /*<<< orphan*/  platform_gpio_mode (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_pwm_get_clock (unsigned int) ; 
 int /*<<< orphan*/  pwm_add (unsigned int) ; 
 int /*<<< orphan*/  pwm_set_duty (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pwm_set_freq (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pwm_start () ; 
 unsigned int* pwms_duty ; 

uint32_t platform_pwm_setup( unsigned pin, uint32_t frequency, unsigned duty )
{
  uint32_t clock;
  if ( pin < NUM_PWM)
  {
    platform_gpio_mode(pin, PLATFORM_GPIO_OUTPUT, PLATFORM_GPIO_FLOAT);  // disable gpio interrupt first
    if(!pwm_add(pin))
      return 0;
    // pwm_set_duty(DUTY(duty), pin);
    pwm_set_duty(0, pin);
    pwms_duty[pin] = duty;
    pwm_set_freq((uint16_t)frequency, pin);
  } else {
    return 0;
  }
  clock = platform_pwm_get_clock( pin );
  if (!pwm_start()) {
    return 0;
  }
  return clock;
}