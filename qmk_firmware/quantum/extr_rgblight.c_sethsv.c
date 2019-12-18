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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  LED_TYPE ;

/* Variables and functions */
 scalar_t__ RGBLIGHT_LIMIT_VAL ; 
 int /*<<< orphan*/  sethsv_raw (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

void sethsv(uint8_t hue, uint8_t sat, uint8_t val, LED_TYPE *led1) { sethsv_raw(hue, sat, val > RGBLIGHT_LIMIT_VAL ? RGBLIGHT_LIMIT_VAL : val, led1); }