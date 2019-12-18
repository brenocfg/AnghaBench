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
 int /*<<< orphan*/  clear_macro_mods () ; 
 int /*<<< orphan*/  clear_weak_mods () ; 
 int /*<<< orphan*/  host_consumer_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_system_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousekey_clear () ; 
 int /*<<< orphan*/  mousekey_send () ; 
 int /*<<< orphan*/  send_keyboard_report () ; 

void clear_keyboard_but_mods_and_keys() {
    clear_weak_mods();
    clear_macro_mods();
    send_keyboard_report();
#ifdef MOUSEKEY_ENABLE
    mousekey_clear();
    mousekey_send();
#endif
#ifdef EXTRAKEY_ENABLE
    host_system_send(0);
    host_consumer_send(0);
#endif
}