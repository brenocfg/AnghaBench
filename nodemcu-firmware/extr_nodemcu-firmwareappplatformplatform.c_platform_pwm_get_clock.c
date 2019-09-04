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
 unsigned int NUM_PWM ; 
 int /*<<< orphan*/  pwm_exist (unsigned int) ; 
 int /*<<< orphan*/  pwm_get_freq (unsigned int) ; 

uint32_t platform_pwm_get_clock( unsigned pin )
{
  // NODE_DBG("Function platform_pwm_get_clock() is called.\n");
  if( pin >= NUM_PWM)
    return 0;
  if(!pwm_exist(pin))
    return 0;

  return (uint32_t)pwm_get_freq(pin);
}