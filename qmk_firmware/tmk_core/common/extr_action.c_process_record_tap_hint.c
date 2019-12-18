#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  key; } ;
struct TYPE_11__ {TYPE_1__ event; } ;
typedef  TYPE_4__ keyrecord_t ;
struct TYPE_10__ {int /*<<< orphan*/  code; } ;
struct TYPE_9__ {int id; } ;
struct TYPE_12__ {TYPE_3__ swap; TYPE_2__ kind; } ;
typedef  TYPE_5__ action_t ;

/* Variables and functions */
#define  ACT_SWAP_HANDS 129 
#define  OP_SH_TAP_TOGGLE 128 
 TYPE_5__ layer_switch_get_action (int /*<<< orphan*/ ) ; 
 int swap_hands ; 
 int swap_held ; 

void process_record_tap_hint(keyrecord_t *record) {
    action_t action = layer_switch_get_action(record->event.key);

    switch (action.kind.id) {
#    ifdef SWAP_HANDS_ENABLE
        case ACT_SWAP_HANDS:
            switch (action.swap.code) {
                case OP_SH_TAP_TOGGLE:
                default:
                    swap_hands = !swap_hands;
                    swap_held  = true;
            }
            break;
#    endif
    }
}