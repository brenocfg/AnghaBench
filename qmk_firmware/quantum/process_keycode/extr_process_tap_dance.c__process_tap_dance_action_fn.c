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
typedef  int /*<<< orphan*/  (* qk_tap_dance_user_fn_t ) (int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  qk_tap_dance_state_t ;

/* Variables and functions */

__attribute__((used)) static inline void _process_tap_dance_action_fn(qk_tap_dance_state_t *state, void *user_data, qk_tap_dance_user_fn_t fn) {
    if (fn) {
        fn(state, user_data);
    }
}