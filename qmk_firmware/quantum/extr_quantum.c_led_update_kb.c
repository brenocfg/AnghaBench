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
typedef  int /*<<< orphan*/  led_t ;

/* Variables and functions */
 int led_update_user (int /*<<< orphan*/ ) ; 

__attribute__((weak)) bool led_update_kb(led_t led_state) { return led_update_user(led_state); }