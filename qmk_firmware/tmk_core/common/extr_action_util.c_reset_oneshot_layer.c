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

/* Variables and functions */
 int /*<<< orphan*/  get_oneshot_layer () ; 
 int /*<<< orphan*/  oneshot_layer_changed_kb (int /*<<< orphan*/ ) ; 
 scalar_t__ oneshot_layer_data ; 
 scalar_t__ oneshot_layer_time ; 

void reset_oneshot_layer(void) {
    oneshot_layer_data = 0;
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_layer_time = 0;
#    endif
    oneshot_layer_changed_kb(get_oneshot_layer());
}