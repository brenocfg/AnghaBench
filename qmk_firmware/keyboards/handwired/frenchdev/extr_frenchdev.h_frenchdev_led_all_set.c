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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  frenchdev_led_1_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frenchdev_led_2_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frenchdev_led_3_set (int /*<<< orphan*/ ) ; 

inline void frenchdev_led_all_set(uint8_t n)
{
    frenchdev_led_1_set(n);
    frenchdev_led_2_set(n);
    frenchdev_led_3_set(n);
}