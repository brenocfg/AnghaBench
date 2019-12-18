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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NORMAL_DUTY (int /*<<< orphan*/ ) ; 
 unsigned int NUM_PWM ; 
 int /*<<< orphan*/  pwm_exist (unsigned int) ; 
 int /*<<< orphan*/  pwm_get_duty (unsigned int) ; 
 int /*<<< orphan*/  pwm_set_duty (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pwm_start () ; 
 int /*<<< orphan*/ * pwms_duty ; 

uint32_t platform_pwm_set_duty( unsigned pin, uint32_t duty )
{
  // NODE_DBG("Function platform_pwm_set_duty() is called.\n");
  if ( pin < NUM_PWM)
  {
    if(!pwm_exist(pin))
      return 0;
    pwm_set_duty(DUTY(duty), pin);
  } else {
    return 0;
  }
  pwm_start();
  pwms_duty[pin] = NORMAL_DUTY(pwm_get_duty(pin));
  return pwms_duty[pin];
}