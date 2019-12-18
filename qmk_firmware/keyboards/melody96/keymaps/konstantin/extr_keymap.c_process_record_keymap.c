#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_7__ {int /*<<< orphan*/  v; int /*<<< orphan*/  s; int /*<<< orphan*/  h; } ;

/* Variables and functions */
#define  RGB_SET 128 
 size_t cidx ; 
 size_t cnum ; 
 TYPE_4__** colors ; 
 int /*<<< orphan*/  rgblight_sethsv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RGB_SET:
        if (record->event.pressed) {
            cidx = (cidx + 1) % cnum;
            rgblight_sethsv(colors[cidx]->h, colors[cidx]->s, colors[cidx]->v);
        }
        break;
    }

    return true;
}