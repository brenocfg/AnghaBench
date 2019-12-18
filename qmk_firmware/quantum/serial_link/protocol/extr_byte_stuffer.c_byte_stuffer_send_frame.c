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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  send_block (scalar_t__,scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  send_data (scalar_t__,scalar_t__ const*,int) ; 

void byte_stuffer_send_frame(uint8_t link, uint8_t* data, uint16_t size) {
    const uint8_t zero = 0;
    if (size > 0) {
        uint16_t num_non_zero = 1;
        uint8_t* end          = data + size;
        uint8_t* start        = data;
        while (data < end) {
            if (num_non_zero == 0xFF) {
                // There's more data after big non-zero block
                // So send it, and start a new block
                send_block(link, start, data, num_non_zero);
                start        = data;
                num_non_zero = 1;
            } else {
                if (*data == 0) {
                    // A zero encountered, so send the block
                    send_block(link, start, data, num_non_zero);
                    start        = data + 1;
                    num_non_zero = 1;
                } else {
                    num_non_zero++;
                }
                ++data;
            }
        }
        send_block(link, start, data, num_non_zero);
        send_data(link, &zero, 1);
    }
}