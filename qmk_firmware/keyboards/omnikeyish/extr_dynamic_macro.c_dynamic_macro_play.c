#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {size_t length; int /*<<< orphan*/ * events; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  dprintf (char*,size_t,size_t) ; 
 TYPE_1__* dynamic_macros ; 
 int /*<<< orphan*/  layer_clear () ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  process_record (int /*<<< orphan*/ *) ; 

void dynamic_macro_play(uint8_t macro_id) {
  dprintf("dynamic macro: slot %d playback, length %d\n", macro_id, dynamic_macros[macro_id].length);

  uint32_t saved_layer_state = layer_state;

  clear_keyboard();
  layer_clear();

  for (uint8_t i = 0; i < dynamic_macros[macro_id].length; ++i) {
    process_record(&dynamic_macros[macro_id].events[i]);
  }

  clear_keyboard();

  layer_state = saved_layer_state;
}