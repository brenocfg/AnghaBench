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
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int QK_UNICODE ; 
 int QK_UNICODE_MAX ; 
 int /*<<< orphan*/  register_hex (int) ; 
 int /*<<< orphan*/  unicode_input_finish () ; 
 int /*<<< orphan*/  unicode_input_start () ; 

bool process_unicode(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= QK_UNICODE && keycode <= QK_UNICODE_MAX && record->event.pressed) {
        unicode_input_start();
        register_hex(keycode & 0x7FFF);
        unicode_input_finish();
    }
    return true;
}