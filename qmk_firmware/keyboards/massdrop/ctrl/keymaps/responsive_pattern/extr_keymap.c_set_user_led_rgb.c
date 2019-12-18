#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int state; int r; int g; int b; } ;

/* Variables and functions */
 TYPE_1__* USER_LED ; 

void set_user_led_rgb(uint8_t i, uint8_t r, uint8_t g, uint8_t b){
    USER_LED[i-1].state = 1;
    USER_LED[i-1].r = r;
    USER_LED[i-1].g = g;
    USER_LED[i-1].b = b;
}