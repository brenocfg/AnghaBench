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
 int /*<<< orphan*/  biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer ; 
 int /*<<< orphan*/  layer_state_set_user (int /*<<< orphan*/ ) ; 

uint32_t layer_state_set_kb(uint32_t state) {
  state = layer_state_set_user(state);
  layer = biton32(state);
  return state;
}