#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_6__ {scalar_t__ pressed; } ;
struct TYPE_7__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_8__ {int mods; } ;

/* Variables and functions */
 int BABL_NUM_MACROS ; 
 int BABL_START_NUM ; 
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
#define  DHPASTE 129 
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  ESC ; 
 int /*<<< orphan*/  KC_D ; 
 int /*<<< orphan*/  KC_LGUI ; 
 int /*<<< orphan*/  KC_RSFT ; 
 int /*<<< orphan*/  KC_V ; 
 int /*<<< orphan*/  LSFT ; 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLN ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U (int /*<<< orphan*/ ) ; 
#define  VIBRK 128 
 int /*<<< orphan*/  babblePaste (TYPE_2__*,int) ; 
 int /*<<< orphan*/  clear_keyboard_but_mods () ; 
 TYPE_3__* keyboard_report ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{

/* If id is in the range of BABL macros, call the babl function */
/* Any clever remapping with modifiers should happen here e.g. shift bablkey does opposite*/
#ifdef USE_BABLPASTE

   if( id >= BABL_START_NUM && id < (BABL_START_NUM + BABL_NUM_MACROS ) ) {
   		if (record->event.pressed)  { // is there a case where this isn't desired?

   			babblePaste ( record,  id );
   			return MACRO_NONE;
   		}
   	}
#endif


  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;

 /* Colemak mod-dh moves the D key to the qwerty V position
   This hack makes apple-V_position do what I mean */
 	case DHPASTE:
		if(keyboard_report->mods & MOD_BIT(KC_LGUI) ) {
			if (record->event.pressed) {
	  	 		clear_keyboard_but_mods();
		 		register_code(KC_V);
	     	} else {
		 		unregister_code(KC_V);
	    	}
		} else {
            if (record->event.pressed) {
          		register_code(KC_D);
            } else {
           		unregister_code(KC_D);
	   		}
		}
	break;

	case VIBRK: // vi esc:
		 if (record->event.pressed) {
			return MACRO( T(ESC),D(LSFT),T(SCLN),U(LSFT), END );
		 }
	break;




	default:
    	return MACRO_NONE;
    }


return MACRO_NONE;
}