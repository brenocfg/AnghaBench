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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LR_KBCTL ; 
 int /*<<< orphan*/  LR_SYMBOL ; 
 int /*<<< orphan*/  LR_SYSCTL ; 
 int /*<<< orphan*/  layer_state_set_user_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t layer_state_set_user(uint32_t state) {
  uint32_t intermediate_state = update_tri_layer_state(state, LR_SYMBOL, LR_SYSCTL, LR_KBCTL);
  intermediate_state = layer_state_set_user_local(intermediate_state);
  return intermediate_state;
}