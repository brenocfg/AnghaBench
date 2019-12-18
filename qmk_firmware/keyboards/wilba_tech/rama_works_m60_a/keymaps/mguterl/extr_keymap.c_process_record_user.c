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
#define  FN_HHKB 129 
#define  FN_UTIL 128 
 int /*<<< orphan*/  layer_off (int) ; 
 int /*<<< orphan*/  layer_on (int) ; 
 int /*<<< orphan*/  update_tri_layer (int,int,int) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	switch(keycode) {
		case FN_HHKB:
			if (record->event.pressed) {
				layer_on(2);
				update_tri_layer(2, 3, 4);
			} else {
				layer_off(2);
				update_tri_layer(2, 3, 4);
			}
			return false;
			break;
		case FN_UTIL:
			if (record->event.pressed) {
				layer_on(3);
				update_tri_layer(2, 3, 4);
			} else {
				layer_off(3);
				update_tri_layer(2, 3, 4);
			}
			return false;
			break;
    default:
      return true;
	}
}