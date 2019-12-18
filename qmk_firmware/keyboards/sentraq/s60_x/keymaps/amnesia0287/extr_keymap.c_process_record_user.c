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
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  FN_HLa 129 
#define  FN_HLb 128 
 int /*<<< orphan*/  _HL ; 
 int /*<<< orphan*/  _HLa ; 
 int /*<<< orphan*/  _HLb ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FN_HLa:
      if (record->event.pressed)
      {
        layer_on(_HLa);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      else
      {
        layer_off(_HLa);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      return false;
      break;
    case FN_HLb:
      if (record->event.pressed)
      {
        layer_on(_HLb);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      else
      {
        layer_off(_HLb);
        update_tri_layer(_HLa, _HLb, _HL);
      }
      return false;
      break;
  }
  return true;
}