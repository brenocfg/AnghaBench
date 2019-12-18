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
#define  _ADJUST 130 
#define  _LOWER 129 
#define  _RAISE 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_setrgb_chartreuse () ; 
 int /*<<< orphan*/  rgblight_setrgb_pink () ; 
 int /*<<< orphan*/  rgblight_setrgb_red () ; 
 int /*<<< orphan*/  rgblight_setrgb_teal () ; 
 int /*<<< orphan*/  update_tri_layer_state (int /*<<< orphan*/ ,int,int,int) ; 

uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#ifdef RGBLIGHT_ENABLE
    switch (biton32(state)) {
    case _RAISE:
      rgblight_setrgb_chartreuse(); // RAISE:シャルトリューズ
      break;
    case _LOWER:
      rgblight_setrgb_pink(); // LOWER:ピンク
      break;
    case _ADJUST:
      rgblight_setrgb_red(); // ADJUST:レッド
      break;
    default: //  for any other layers, or the default layer
      rgblight_setrgb_teal(); // 他:ティール
      break;
    }
#endif
return state;
}