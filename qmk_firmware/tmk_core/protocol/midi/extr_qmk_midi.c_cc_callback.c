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
typedef  int /*<<< orphan*/  MidiDevice ;

/* Variables and functions */

__attribute__((used)) static void cc_callback(MidiDevice* device, uint8_t chan, uint8_t num, uint8_t val) {
    // sending it back on the next channel
    // midi_send_cc(device, (chan + 1) % 16, num, val);
}