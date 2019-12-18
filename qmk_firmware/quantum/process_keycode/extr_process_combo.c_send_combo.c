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

/* Variables and functions */
 int /*<<< orphan*/  current_combo_index ; 
 int /*<<< orphan*/  process_combo_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  register_code16 (scalar_t__) ; 
 int /*<<< orphan*/  unregister_code16 (scalar_t__) ; 

__attribute__((used)) static inline void send_combo(uint16_t action, bool pressed) {
    if (action) {
        if (pressed) {
            register_code16(action);
        } else {
            unregister_code16(action);
        }
    } else {
        process_combo_event(current_combo_index, pressed);
    }
}