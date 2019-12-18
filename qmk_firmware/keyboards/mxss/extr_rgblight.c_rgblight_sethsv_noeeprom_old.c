#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  sat; int /*<<< orphan*/  hue; } ;
struct TYPE_6__ {scalar_t__ enable; } ;
struct TYPE_5__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ LED_TYPE ;

/* Variables and functions */
 TYPE_4__* fled_hs ; 
 TYPE_3__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_setrgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sethsv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void rgblight_sethsv_noeeprom_old(uint16_t hue, uint8_t sat, uint8_t val) {
  if (rgblight_config.enable) {
    LED_TYPE tmp_led;
    sethsv(hue, sat, val, &tmp_led);
    fled_hs[0].hue = fled_hs[1].hue = hue;
    fled_hs[0].sat = fled_hs[1].sat = sat;
    // dprintf("rgblight set hue [MEMORY]: %u,%u,%u\n", inmem_config.hue, inmem_config.sat, inmem_config.val);
    rgblight_setrgb(tmp_led.r, tmp_led.g, tmp_led.b);
  }
}