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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_oneshot_layer () ; 
 int /*<<< orphan*/  layer_on (int) ; 
 int /*<<< orphan*/  oneshot_layer_changed_kb (int /*<<< orphan*/ ) ; 
 int oneshot_layer_data ; 
 int /*<<< orphan*/  oneshot_layer_time ; 
 int /*<<< orphan*/  timer_read () ; 

void set_oneshot_layer(uint8_t layer, uint8_t state) {
    oneshot_layer_data = layer << 3 | state;
    layer_on(layer);
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_layer_time = timer_read();
#    endif
    oneshot_layer_changed_kb(get_oneshot_layer());
}