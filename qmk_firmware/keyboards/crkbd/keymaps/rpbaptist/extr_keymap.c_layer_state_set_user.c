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
typedef  int /*<<< orphan*/  layer_state_t ;

/* Variables and functions */
#define  _COLEMAKDHM 129 
#define  _GAMING 128 
 int /*<<< orphan*/  _GAMING_EXT ; 
 int /*<<< orphan*/  _NAV ; 
 int /*<<< orphan*/  _NUM ; 
 int /*<<< orphan*/  _UTIL ; 
 int /*<<< orphan*/  default_layer_state ; 
 int get_highest_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(default_layer_state)) {
    case _COLEMAKDHM:
      state = update_tri_layer_state(state, _NUM, _NAV, _UTIL);
      break;
    case _GAMING:
      state = update_tri_layer_state(state, _GAMING_EXT, _NAV, _UTIL);
      break;
  }
  return state;
}