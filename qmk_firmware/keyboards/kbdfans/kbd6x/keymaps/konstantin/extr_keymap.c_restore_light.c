#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  val; int /*<<< orphan*/  sat; int /*<<< orphan*/  hue; int /*<<< orphan*/  raw; } ;
typedef  TYPE_1__ rgblight_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_read_rgblight () ; 
 int /*<<< orphan*/  rgblight_mode_noeeprom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_sethsv_noeeprom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void restore_light(void) {
    rgblight_config_t saved = { .raw = eeconfig_read_rgblight() };
    rgblight_sethsv_noeeprom(saved.hue, saved.sat, saved.val);
    rgblight_mode_noeeprom(saved.mode);
}