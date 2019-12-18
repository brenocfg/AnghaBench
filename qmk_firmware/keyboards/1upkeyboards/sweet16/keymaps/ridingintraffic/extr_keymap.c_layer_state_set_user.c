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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  _EMOJI 130 
#define  _LEDCNTL 129 
#define  _TAPLAND 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _TAPLAND:
        rgblight_setrgb(0, 16, 0); //green
        break;
    case _LEDCNTL:
        rgblight_setrgb(0, 0, 16); //blue
        break;
    case _EMOJI:
        rgblight_setrgb (16, 0, 16); //purple
        break;

    default: //  for any other layers, or the default layer
        rgblight_setrgb (16, 0, 16); //purple
        break;
    }
  return state;
}