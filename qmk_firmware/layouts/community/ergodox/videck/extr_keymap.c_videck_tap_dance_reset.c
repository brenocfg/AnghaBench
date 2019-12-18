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
struct TYPE_4__ {int /*<<< orphan*/  kc2; int /*<<< orphan*/  (* trigger ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  kc1; } ;
typedef  TYPE_1__ videck_tap_dance_tuple_t ;
struct TYPE_5__ {int count; } ;
typedef  TYPE_2__ qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void videck_tap_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
  videck_tap_dance_tuple_t *const tuple = (videck_tap_dance_tuple_t *)user_data;

  if (state->count == 1) {
    unregister_code16 (tuple->kc1);
  } else if (state->count == 2) {
    unregister_code16 (tuple->kc2);
    tuple->trigger(tuple->kc2);
  }
}