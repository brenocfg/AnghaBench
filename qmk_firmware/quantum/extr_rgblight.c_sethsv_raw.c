#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ RGB ;
typedef  int /*<<< orphan*/  LED_TYPE ;
typedef  TYPE_2__ HSV ;

/* Variables and functions */
 TYPE_1__ hsv_to_rgb (TYPE_2__) ; 
 int /*<<< orphan*/  setrgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void sethsv_raw(uint8_t hue, uint8_t sat, uint8_t val, LED_TYPE *led1) {
    HSV hsv = {hue, sat, val};
    RGB rgb = hsv_to_rgb(hsv);
    setrgb(rgb.r, rgb.g, rgb.b, led1);
}