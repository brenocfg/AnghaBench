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
typedef  int uint16_t ;

/* Variables and functions */
#define  FPH_1 136 
#define  FPH_2 135 
#define  FPH_3 134 
#define  FPH_4 133 
#define  FPH_5 132 
#define  FPH_6 131 
#define  FPH_7 130 
#define  FPH_8 129 
#define  FPH_9 128 
 int KC_4 ; 
 int KC_A ; 
 int KC_AMPR ; 
 int KC_ASTR ; 
 int KC_AT ; 
 int KC_B ; 
 int KC_BSLS ; 
 int KC_C ; 
 int KC_CIRC ; 
 int KC_COMM ; 
 int KC_D ; 
 int KC_DOT ; 
 int KC_E ; 
 int KC_EXLM ; 
 int KC_F ; 
 int KC_G ; 
 int KC_H ; 
 int KC_HASH ; 
 int KC_I ; 
 int KC_J ; 
 int KC_K ; 
 int KC_L ; 
 int KC_LBRC ; 
 int KC_LCBR ; 
 int KC_M ; 
 int KC_MINS ; 
 int KC_N ; 
 int KC_NO ; 
 int KC_O ; 
 int KC_P ; 
 int KC_PERC ; 
 int KC_PIPE ; 
 int KC_PLUS ; 
 int KC_Q ; 
 int KC_QUOT ; 
 int KC_R ; 
 int KC_RBRC ; 
 int KC_RCBR ; 
 int KC_S ; 
 int KC_SCLN ; 
 int KC_SLSH ; 
 int KC_T ; 
 int KC_TILD ; 
 int KC_U ; 
 int KC_UNDS ; 
 int KC_V ; 
 int KC_W ; 
 int KC_X ; 
 int KC_Y ; 
 int KC_Z ; 
 int LSFT (int) ; 

uint16_t get_render_keycode(uint16_t keycode, uint16_t tap_qty){ // maybe replace shift with "mods"
  tap_qty--; // reduce by one to match array indexes.
  switch(keycode){
    case FPH_2:
      {uint16_t kc[] = {KC_A, KC_B, KC_C};
       if(tap_qty % 6 > 2)
        return LSFT(kc[tap_qty % 3]);
      return kc[tap_qty % 3];}
    break;
    case FPH_3:
      {uint16_t kc[] = {KC_D, KC_E, KC_F};
       if(tap_qty % 6 > 2)
        return LSFT(kc[tap_qty % 3]);
      return kc[tap_qty % 3];}
    break;
    case FPH_4:
      {uint16_t kc[] = {KC_G, KC_H, KC_I};
       if(tap_qty % 6 > 2)
        return LSFT(kc[tap_qty % 3]);
      return kc[tap_qty % 3];}
    break;
    case FPH_5:
      {uint16_t kc[] = {KC_J, KC_K, KC_L};
       if(tap_qty % 6 > 2)
        return LSFT(kc[tap_qty % 3]);
      return kc[tap_qty % 3];}
    break;
    case FPH_6:
      {uint16_t kc[] = {KC_M, KC_N, KC_O};
       if(tap_qty % 6 > 2)
        return LSFT(kc[tap_qty % 3]);
      return kc[tap_qty % 3];}
    break;
    case FPH_7:
      {uint16_t kc[] = {KC_P, KC_Q, KC_R, KC_S};
       if(tap_qty % 8 > 2)
        return LSFT(kc[tap_qty % 4]);
      return kc[tap_qty % 4];}
    break;
    case FPH_8:
      {uint16_t kc[] = {KC_T, KC_U, KC_V};
       if(tap_qty % 8 > 2)
        return LSFT(kc[tap_qty % 4]);
      return kc[tap_qty % 4];}
    break;
    case FPH_9:
      {uint16_t kc[] = {KC_W, KC_X, KC_Y, KC_Z};
       if(tap_qty % 8 > 2)
        return LSFT(kc[tap_qty % 4]);
      return kc[tap_qty % 4];}
    break;
    case FPH_1:
      {uint16_t kc[] = {KC_COMM, LSFT(KC_SLSH), KC_EXLM, KC_AT, KC_MINS, KC_UNDS, KC_PLUS, \
          KC_SCLN, LSFT(KC_SCLN), KC_QUOT, LSFT(KC_QUOT), KC_TILD, \
          KC_PIPE, KC_BSLS, KC_HASH, LSFT(KC_4), KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, \
          KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, LSFT(KC_COMM), LSFT(KC_DOT)};
      return kc[tap_qty % 26];}
  }
  return KC_NO;
}