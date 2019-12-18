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
typedef  size_t uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOWN_LINK ; 
 int /*<<< orphan*/  UP_LINK ; 
 scalar_t__ is_master ; 
 int /*<<< orphan*/  validator_send_frame (int /*<<< orphan*/ ,int*,size_t) ; 

void router_send_frame(uint8_t destination, uint8_t* data, uint16_t size) {
    if (destination == 0) {
        if (!is_master) {
            data[size] = 1;
            validator_send_frame(UP_LINK, data, size + 1);
        }
    } else {
        if (is_master) {
            data[size] = destination;
            validator_send_frame(DOWN_LINK, data, size + 1);
        }
    }
}