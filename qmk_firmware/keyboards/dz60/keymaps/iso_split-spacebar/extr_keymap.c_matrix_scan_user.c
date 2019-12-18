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
#define  BL 131 
#define  FL 130 
#define  NL 129 
 int /*<<< orphan*/  RGB_BL_LIGHT ; 
 int /*<<< orphan*/  RGB_BL_MODE ; 
 int /*<<< orphan*/  RGB_FL_LIGHT ; 
 int /*<<< orphan*/  RGB_FL_MODE ; 
 int /*<<< orphan*/  RGB_NL_MODE ; 
 int /*<<< orphan*/  RGB_RL_MODE ; 
#define  RL 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_state ; 

void matrix_scan_user(void) {

  #ifdef RGBLIGHT_ENABLE

  static uint8_t old_layer = 1;
  uint8_t new_layer = biton32(layer_state);

  if (old_layer != new_layer) {
    switch (new_layer) {
      case BL:
          RGB_BL_MODE;
          RGB_BL_LIGHT;        
        break;
      case FL:
          RGB_FL_MODE;
          RGB_FL_LIGHT;  
        break;
      case NL:
          RGB_NL_MODE; 
         // RGB_NL_LIGHT; 
        break;
      case RL:
          RGB_RL_MODE; 
         // RGB_RL_LIGHT;        
        break;
    }

    old_layer = new_layer;
  }

  #endif //RGBLIGHT_ENABLE

}