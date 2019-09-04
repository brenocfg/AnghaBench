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
 int NUM_PWM ; 
 int /*<<< orphan*/  pwm_init (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pwms_duty ; 

void platform_pwm_init()
{
  int i;
  for(i=0;i<NUM_PWM;i++){
    pwms_duty[i] = DUTY(0);
  }
  pwm_init(500, NULL);
  // NODE_DBG("Function pwms_init() is called.\n");
}