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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  keyrecord_t ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  RGB_LAYER0_mode ; 
#define  RGB_MOD 128 
 TYPE_1__ rgblight_config ; 

bool process_record_user(uint16_t keycode, keyrecord_t * record) {
  switch (keycode) {
  case RGB_MOD:
    RGB_LAYER0_mode = rgblight_config.mode;
    break;
  default:
    return (true);
  }
  return (true);
}