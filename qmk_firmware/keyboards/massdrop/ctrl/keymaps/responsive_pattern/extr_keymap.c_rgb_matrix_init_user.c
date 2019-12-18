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
 int ANIMATION_SPEED_STEP ; 
 int led_animation_speed ; 
 int led_per_run ; 

void rgb_matrix_init_user(void){
    led_animation_speed = ANIMATION_SPEED_STEP * 15;
    led_per_run = 15;
}