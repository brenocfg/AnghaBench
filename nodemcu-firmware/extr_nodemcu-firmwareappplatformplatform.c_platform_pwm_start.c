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
 int /*<<< orphan*/  DUTY (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 unsigned int NUM_PWM ; 
 int /*<<< orphan*/  pwm_exist (unsigned int) ; 
 int /*<<< orphan*/  pwm_set_duty (int /*<<< orphan*/ ,unsigned int) ; 
 int pwm_start () ; 
 int /*<<< orphan*/ * pwms_duty ; 

bool platform_pwm_start( unsigned pin )
{
  // NODE_DBG("Function platform_pwm_start() is called.\n");
  if ( pin < NUM_PWM)
  {
    if(!pwm_exist(pin))
      return FALSE;
    pwm_set_duty(DUTY(pwms_duty[pin]), pin);
    return pwm_start();
  }

  return FALSE;
}