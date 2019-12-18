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
 int /*<<< orphan*/  frenchdev_board_led_off () ; 
 int /*<<< orphan*/  frenchdev_led_1_off () ; 
 int /*<<< orphan*/  frenchdev_led_2_off () ; 
 int /*<<< orphan*/  frenchdev_led_3_off () ; 

inline void frenchdev_led_all_off(void)
{
    frenchdev_board_led_off();
    frenchdev_led_1_off();
    frenchdev_led_2_off();
    frenchdev_led_3_off();
}