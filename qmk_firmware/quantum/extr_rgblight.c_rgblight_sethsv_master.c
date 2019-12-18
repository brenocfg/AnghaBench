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
typedef  int uint8_t ;

/* Variables and functions */
 scalar_t__ RGBLED_NUM ; 
 int /*<<< orphan*/  rgblight_sethsv_range (int,int,int,int /*<<< orphan*/ ,int) ; 

void rgblight_sethsv_master(uint8_t hue, uint8_t sat, uint8_t val) { rgblight_sethsv_range(hue, sat, val, 0, (uint8_t)RGBLED_NUM / 2); }