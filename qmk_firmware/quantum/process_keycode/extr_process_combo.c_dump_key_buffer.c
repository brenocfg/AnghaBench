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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  action_t ;
struct TYPE_5__ {int /*<<< orphan*/  key; int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;

/* Variables and functions */
 scalar_t__ buffer_size ; 
 TYPE_2__* key_buffer ; 
 int /*<<< orphan*/  process_action (TYPE_2__*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  register_code16 (TYPE_2__) ; 
 int /*<<< orphan*/  send_keyboard_report () ; 
 int /*<<< orphan*/  store_or_get_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dump_key_buffer(bool emit) {
    if (buffer_size == 0) {
        return;
    }

    if (emit) {
        for (uint8_t i = 0; i < buffer_size; i++) {
#ifdef COMBO_ALLOW_ACTION_KEYS
            const action_t action = store_or_get_action(key_buffer[i].event.pressed, key_buffer[i].event.key);
            process_action(&(key_buffer[i]), action);
#else
            register_code16(key_buffer[i]);
            send_keyboard_report();
#endif
        }
    }

    buffer_size = 0;
}