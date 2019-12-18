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
#define  FN_LAYER 132 
#define  GAMING 131 
#define  NAV_CLUSTER 130 
#define  QWERTY 129 
 int /*<<< orphan*/  RGBLIGHT_MODE_RAINBOW_SWIRL ; 
#define  SQLMACROS 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgblight_mode (int) ; 

uint32_t layer_state_set_user(uint32_t state)
{
  switch (biton32(state))
  {
    case QWERTY:
      rgblight_mode(9);
      break;
    case NAV_CLUSTER:
      rgblight_mode(29);
      break;
    case GAMING:
      rgblight_mode(26);
      break;
    case SQLMACROS:
      rgblight_mode(1);
      break;
    case FN_LAYER:
      rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL+5);
      break;
  }
  return state;
}