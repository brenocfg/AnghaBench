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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 scalar_t__ TAPPING_TERM ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_string (char*) ; 
 int /*<<< orphan*/  sunds_timer ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void mod_or_mod_with_macro(keyrecord_t *record, uint16_t kc_mod, char* macro) {
    if (record->event.pressed) {
        sunds_timer = timer_read();
        register_code(kc_mod);
    } else {
        if (timer_elapsed(sunds_timer) < TAPPING_TERM) {
            send_string(macro);
        }
        unregister_code(kc_mod);
    }
}