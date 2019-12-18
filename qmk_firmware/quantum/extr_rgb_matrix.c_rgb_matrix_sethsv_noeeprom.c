#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {scalar_t__ v; void* s; int /*<<< orphan*/  h; } ;
struct TYPE_4__ {TYPE_1__ hsv; } ;

/* Variables and functions */
 scalar_t__ RGB_MATRIX_MAXIMUM_BRIGHTNESS ; 
 TYPE_2__ rgb_matrix_config ; 

void rgb_matrix_sethsv_noeeprom(uint16_t hue, uint8_t sat, uint8_t val) {
    rgb_matrix_config.hsv.h = hue;
    rgb_matrix_config.hsv.s = sat;
    rgb_matrix_config.hsv.v = val;
    if (rgb_matrix_config.hsv.v > RGB_MATRIX_MAXIMUM_BRIGHTNESS) rgb_matrix_config.hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
}