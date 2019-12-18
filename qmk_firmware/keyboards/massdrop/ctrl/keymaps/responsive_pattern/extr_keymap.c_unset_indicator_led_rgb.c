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
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 TYPE_1__* USER_LED ; 

void unset_indicator_led_rgb(uint8_t i, uint8_t layer){
    USER_LED[i-1].state &= ~(1 << layer);
}