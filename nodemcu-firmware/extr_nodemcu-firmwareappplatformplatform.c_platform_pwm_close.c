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
 unsigned int NUM_PWM ; 
 int /*<<< orphan*/  pwm_delete (unsigned int) ; 
 int /*<<< orphan*/  pwm_start () ; 

void platform_pwm_close( unsigned pin )
{
  // NODE_DBG("Function platform_pwm_stop() is called.\n");
  if ( pin < NUM_PWM)
  {
    pwm_delete(pin);
    pwm_start();
  }
}