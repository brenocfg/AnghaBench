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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  oneshot_fullfillment_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_oneshot_layer () ; 
 int /*<<< orphan*/  get_oneshot_layer_state () ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oneshot_layer_data ; 
 int /*<<< orphan*/  reset_oneshot_layer () ; 

void clear_oneshot_layer_state(oneshot_fullfillment_t state) {
    uint8_t start_state = oneshot_layer_data;
    oneshot_layer_data &= ~state;
    if (!get_oneshot_layer_state() && start_state != oneshot_layer_data) {
        layer_off(get_oneshot_layer());
        reset_oneshot_layer();
    }
}