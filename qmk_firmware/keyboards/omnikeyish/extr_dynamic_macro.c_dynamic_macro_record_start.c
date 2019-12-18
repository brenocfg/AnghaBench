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
struct TYPE_2__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  dprintf (char*,size_t) ; 
 int /*<<< orphan*/  dynamic_macro_led_blink () ; 
 TYPE_1__* dynamic_macros ; 
 int /*<<< orphan*/  layer_clear () ; 

void dynamic_macro_record_start(uint8_t macro_id) {
  dprintf("dynamic macro recording: started for slot %d\n", macro_id);

  dynamic_macro_led_blink();

  clear_keyboard();
  layer_clear();

  dynamic_macros[macro_id].length = 0;
}