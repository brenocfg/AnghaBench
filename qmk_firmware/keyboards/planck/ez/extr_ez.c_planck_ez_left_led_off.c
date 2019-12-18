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
 int /*<<< orphan*/  PWMD4 ; 
 int /*<<< orphan*/  pwmDisableChannel (int /*<<< orphan*/ *,int) ; 

void planck_ez_left_led_off(void){
    pwmDisableChannel(&PWMD4, 3);
}