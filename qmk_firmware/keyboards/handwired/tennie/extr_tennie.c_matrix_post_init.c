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
 int /*<<< orphan*/  keyboard_post_init_user () ; 
 int /*<<< orphan*/  rgblight_enable_noeeprom () ; 

void matrix_post_init(void) {
	rgblight_enable_noeeprom();
	keyboard_post_init_user();
}