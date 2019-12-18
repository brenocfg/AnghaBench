#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* send_func ) (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ MidiDevice ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void midi_send_data(MidiDevice* device, uint16_t count, uint8_t byte0, uint8_t byte1, uint8_t byte2) {
    // ensure that the count passed along is always 3 or lower
    if (count > 3) {
        // TODO how to do this correctly?
    }
    device->send_func(device, count, byte0, byte1, byte2);
}