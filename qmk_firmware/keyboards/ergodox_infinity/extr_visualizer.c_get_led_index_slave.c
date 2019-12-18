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
typedef  int /*<<< orphan*/  visualizer_user_data_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int get_led_index_master (int /*<<< orphan*/ *) ; 
 scalar_t__ is_led_on (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint8_t get_led_index_slave(visualizer_user_data_t* user_data) {
    uint8_t master_index = get_led_index_master(user_data);
    if (master_index!=0) {
        for (int i=master_index; i < 3; i++) {
            if (is_led_on(user_data, i)) {
                return i + 1;
            }
        }
    }

    return 0;
}