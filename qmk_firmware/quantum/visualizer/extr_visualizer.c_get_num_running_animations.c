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
 int MAX_SIMULTANEOUS_ANIMATIONS ; 
 scalar_t__* animations ; 

__attribute__((used)) static uint8_t get_num_running_animations(void) {
    uint8_t count = 0;
    for (int i = 0; i < MAX_SIMULTANEOUS_ANIMATIONS; i++) {
        count += animations[i] ? 1 : 0;
    }
    return count;
}