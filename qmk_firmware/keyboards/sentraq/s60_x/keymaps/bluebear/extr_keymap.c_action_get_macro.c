#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSLS ; 
 int /*<<< orphan*/  DOT ; 
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int /*<<< orphan*/  MINS ; 
 int /*<<< orphan*/  SPACE ; 
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int mc_shift_on ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  switch(id) {

  case 0: //Number 0-)
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(MINS), T(DOT), T(MINS), T(MINS), T(DOT), T(MINS), T(SPACE), END); //-.--.-
	  }
	  else {
		return MACRO(T(MINS), T(MINS), T(MINS), T(MINS), T(MINS), T(SPACE), END); //-----
	  }
	}
	break;

  case 1: //Number 1-!
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(MINS), T(DOT), T(MINS), T(DOT), T(MINS), T(MINS), T(SPACE), END); //-.-.--
	  }
	  else {
		return MACRO(T(DOT), T(MINS), T(MINS), T(MINS), T(MINS), T(SPACE), END); //.----
	  }
	}
	break;

  case 2: //Number 2-@
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(MINS), T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //.--.-.
	  }
	  else {
		return MACRO(T(DOT), T(DOT), T(MINS), T(MINS), T(MINS), T(SPACE), END); //..---
	  }
	}
	break;

  case 3: // Number 3
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(DOT), T(MINS), T(MINS), T(SPACE), END); //...--
	}
	break;

  case 4: //Number 4-$
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(DOT), T(DOT), T(MINS), T(DOT), T(DOT), T(MINS), T(SPACE), END); //...-..-
	  }
	  else {
		return MACRO(T(DOT), T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //....-
	  }
	}
	break;

  case 5: //Number 5
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(DOT), T(DOT), T(DOT), T(SPACE), END); //.....
	}
	break;

  case 6: //Number 6
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(DOT), T(SPACE), END); //-....
	}
	break;

  case 7: //Number 7-&
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //.-...
	  }
	  else {
		return MACRO(T(MINS), T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //--...
	  }
	}
	break;

  case 8: //Number 8
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(MINS), T(DOT), T(DOT), T(SPACE), END); //---..
	}
	break;

  case 9: //Number 9-(
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(MINS), T(DOT), T(MINS), T(MINS), T(DOT), T(SPACE), END); //-.--.
	  }
	  else {
		return MACRO(T(MINS), T(MINS), T(MINS), T(MINS), T(DOT), T(SPACE), END); //----.
	  }
	}
	break;

  case 10: //Letter A
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(SPACE), END); //.-
	}
	break;

  case 11: //Letter B
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //-...
	}
	break;

  case 12: //Letter C
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //-.-.
	}
	break;

  case 13: //Letter D
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(DOT), T(SPACE), END); //-..
	}
	break;

  case 14: //Letter E
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(SPACE), END); //.
	}
	break;

  case 15: //Letter F
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(MINS), T(DOT), T(SPACE), END); //..-.
	}
	break;

  case 16: //Letter G
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(DOT), T(SPACE), END); //--.
	}
	break;

  case 17: //Letter H
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(DOT), T(DOT), T(SPACE), END); //....
	}
	break;

  case 18: //Letter I
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(SPACE), END); //..
	}
	break;

  case 19: //Letter J
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(MINS), T(MINS), T(SPACE), END); //.---
	}
	break;

  case 20: //Letter K
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(MINS), T(SPACE), END); //-.-
	}
	break;

  case 21: //Letter L
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(DOT), T(DOT), T(SPACE), END); //.-..
	}
	break;

  case 22: //Letter M
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(SPACE), END); //--
	}
	break;

  case 23: //Letter N
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(SPACE), END); //-.
	}
	break;

  case 24: //Letter O
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(MINS), T(SPACE), END); //---
	}
	break;

  case 25: //Letter P
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(MINS), T(DOT), T(SPACE), END); //.--.
	}
	break;

  case 26: //Letter Q
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(DOT), T(MINS), T(SPACE), END); //--.-
	}
	break;

  case 27: //Letter R
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(DOT), T(SPACE), END); //.-.
	}
	break;

  case 28: //Letter S
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(DOT), T(SPACE), END); //...
	}
	break;

  case 29: //Letter T
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(SPACE), END); //-
	}
	break;

  case 30: //Letter U
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(MINS), T(SPACE), END); //..-
	}
	break;

  case 31: //Letter V
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //...-
	}
	break;

  case 32: //Letter W
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(MINS), T(SPACE), END); //.--
	}
	break;

  case 33: //Letter X
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(DOT), T(MINS), T(SPACE), END); //-..-
	}
	break;

  case 34: //Letter Y
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
	  }
	  return MACRO(T(MINS), T(DOT), T(MINS), T(MINS), T(SPACE), END); //-.--
	}
	break;

  case 35: //Letter Z
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(DOT), T(DOT), T(SPACE), END); //--..
	}
	break;

  case 36: //Punctuation .
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(DOT), T(MINS), T(DOT), T(MINS), T(SPACE), END); //.-.-.-
	}
	break;

  case 37: //Punctuation ,
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(DOT), T(DOT), T(MINS), T(MINS), T(SPACE), END); //--..--
	}
	break;

  case 38: //Punctuation '-"
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(MINS), T(DOT), T(DOT), T(MINS), T(DOT), T(SPACE), END); //.-..-.
	  }
	  else {
		return MACRO(T(DOT), T(MINS), T(MINS), T(MINS), T(MINS), T(DOT), T(SPACE), END); //-....-
	  }
	}
	break;

  case 39: //Punctuation /-?
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(DOT), T(MINS), T(MINS), T(DOT), T(DOT), T(SPACE), END); //..--..
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(DOT), T(MINS), T(DOT), T(SPACE), END); //-..-.
	  }
	}
	break;

  case 40: //Punctuation ;-:
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(MINS), T(MINS), T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //---...
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //-.-.-.
	  }
	}
	break;

  case 41: //Punctuation =-+
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //.-.-.
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //-...-
	  }
	}
	break;

  case 42: //Punctuation --_
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(DOT), T(MINS), T(MINS), T(DOT), T(MINS), T(SPACE), END); //..--.-
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //-....-
	  }
	}
	break;

  case 43: //Morse Space
	if (record->event.pressed) {
	  return MACRO(T(BSLS), T(SPACE), END); //When pressed, this sends a slash followed by a space, making it easier to distinguish words in Morse
	}
	break;
  }
  return MACRO_NONE;
}