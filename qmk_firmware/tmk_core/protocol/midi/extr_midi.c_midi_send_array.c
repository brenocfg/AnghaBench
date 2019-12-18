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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  MidiDevice ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  midi_send_data (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void midi_send_array(MidiDevice* device, uint16_t count, uint8_t* array) {
    uint16_t i;
    for (i = 0; i < count; i += 3) {
        uint8_t  b[3]    = {0, 0, 0};
        uint16_t to_send = count - i;
        to_send          = (to_send > 3) ? 3 : to_send;
        memcpy(b, array + i, to_send);
        midi_send_data(device, to_send, b[0], b[1], b[2]);
    }
}