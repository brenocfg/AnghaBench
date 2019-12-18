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

/* Variables and functions */
 int KC_LALT ; 
 int KC_LCTL ; 
 int KC_LGUI ; 
 int KC_LSFT ; 
 int QK_LALT ; 
 int QK_LCTL ; 
 int QK_LGUI ; 
 int QK_LSFT ; 
 int delay_registered_code ; 
 int /*<<< orphan*/  unregister_code (int) ; 

void unregister_delay_code(void){
  if(delay_registered_code){
    unregister_code(delay_registered_code);
    if (delay_registered_code & QK_LSFT){
      unregister_code(KC_LSFT);
    }
    if (delay_registered_code & QK_LCTL){
      unregister_code(KC_LCTL);
    }
    if (delay_registered_code & QK_LALT){
      unregister_code(KC_LALT);
    }
    if (delay_registered_code & QK_LGUI){
      unregister_code(KC_LGUI);
    }
    delay_registered_code=0;
  }
}