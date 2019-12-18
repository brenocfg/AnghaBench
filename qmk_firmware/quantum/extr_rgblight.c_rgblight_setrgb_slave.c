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
 int /*<<< orphan*/  rgblight_setrgb_range (int,int,int,int,int) ; 

void rgblight_setrgb_slave(uint8_t r, uint8_t g, uint8_t b) { rgblight_setrgb_range(r, g, b, (uint8_t)RGBLED_NUM / 2, (uint8_t)RGBLED_NUM); }