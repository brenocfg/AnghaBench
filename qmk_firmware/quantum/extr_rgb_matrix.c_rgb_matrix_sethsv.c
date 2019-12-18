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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_update_rgb_matrix () ; 
 int /*<<< orphan*/  rgb_matrix_sethsv_noeeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rgb_matrix_sethsv(uint16_t hue, uint8_t sat, uint8_t val) {
    rgb_matrix_sethsv_noeeprom(hue, sat, val);
    eeconfig_update_rgb_matrix();
}