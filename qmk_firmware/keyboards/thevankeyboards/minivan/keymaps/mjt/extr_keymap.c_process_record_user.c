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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */
 scalar_t__ ADJUST ; 
 scalar_t__ DYN_REC_STOP ; 
 scalar_t__ FKEYGRV ; 
 scalar_t__ FKEYS ; 
 int /*<<< orphan*/  process_record_dynamic_macro (scalar_t__,int /*<<< orphan*/ *) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint16_t macro_kc = keycode;
  if (keycode == FKEYS || keycode == ADJUST || keycode == FKEYGRV ){
    macro_kc = DYN_REC_STOP;
  }
  if (!process_record_dynamic_macro(macro_kc, record)) {
    return false;
  }

  return true;
}