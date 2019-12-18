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
 void* RGB_encoder_timer ; 
 void* RGB_encoder_timer2 ; 
 void* timer_read () ; 

void matrix_init_user(void) {
  RGB_encoder_timer = timer_read();
  RGB_encoder_timer2 = timer_read();
}