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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ DOWN_LINK ; 
 scalar_t__ UP_LINK ; 
 scalar_t__ is_master ; 
 int /*<<< orphan*/  transport_recv_frame (scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  validator_send_frame (scalar_t__,scalar_t__*,int) ; 

void route_incoming_frame(uint8_t link, uint8_t* data, uint16_t size) {
    if (is_master) {
        if (link == DOWN_LINK) {
            transport_recv_frame(data[size - 1], data, size - 1);
        }
    } else {
        if (link == UP_LINK) {
            if (data[size - 1] & 1) {
                transport_recv_frame(0, data, size - 1);
            }
            data[size - 1] >>= 1;
            validator_send_frame(DOWN_LINK, data, size);
        } else {
            data[size - 1]++;
            validator_send_frame(UP_LINK, data, size);
        }
    }
}