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
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ crc32_byte (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  route_incoming_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void validator_recv_frame(uint8_t link, uint8_t* data, uint16_t size) {
    if (size > 4) {
        uint32_t frame_crc;
        memcpy(&frame_crc, data + size - 4, 4);
        uint32_t expected_crc = crc32_byte(data, size - 4);
        if (frame_crc == expected_crc) {
            route_incoming_frame(link, data, size - 4);
        }
    }
}