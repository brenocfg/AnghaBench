#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  DYN_REC_START1 130 
#define  DYN_REC_START2 129 
#define  DYN_REC_STOP 128 
 int /*<<< orphan*/  process_record_dynamic_macro (int,TYPE_2__*) ; 
 int recording_dynamic_macro ; 

__attribute__((used)) static bool process_record_dynamic_macro_wrapper(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /* detect dynamic macro recording state */
    case DYN_REC_START1:
    case DYN_REC_START2:
      if (record->event.pressed) {
        recording_dynamic_macro = true;
      }
      break;
    case DYN_REC_STOP:
      if (record->event.pressed) {
        recording_dynamic_macro = false;
      }
      break;
  }

  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  return true;
}