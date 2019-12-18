#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  reserved; int /*<<< orphan*/  mods; int /*<<< orphan*/ * keys; } ;
typedef  TYPE_1__ report_keyboard_t ;

/* Variables and functions */
 int KEYBOARD_REPORT_KEYS ; 
 int /*<<< orphan*/  debug_hex8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_keyboard ; 
 int /*<<< orphan*/  dprintf (char*) ; 

void bluefruit_keyboard_print_report(report_keyboard_t *report) {
    if (!debug_keyboard) return;
    dprintf("keys: ");
    for (int i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        debug_hex8(report->keys[i]);
        dprintf(" ");
    }
    dprintf(" mods: ");
    debug_hex8(report->mods);
    dprintf(" reserved: ");
    debug_hex8(report->reserved);
    dprintf("\n");
}