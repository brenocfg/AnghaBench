#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ byteQueueIndex_t ;
struct TYPE_5__ {int /*<<< orphan*/  input_queue; int /*<<< orphan*/  (* pre_input_process_callback ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ MidiDevice ;

/* Variables and functions */
 int /*<<< orphan*/  bytequeue_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bytequeue_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytequeue_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  midi_process_byte (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void midi_device_process(MidiDevice* device) {
    // call the pre_input_process_callback if there is one
    if (device->pre_input_process_callback) device->pre_input_process_callback(device);

    // pull stuff off the queue and process
    byteQueueIndex_t len = bytequeue_length(&device->input_queue);
    uint16_t         i;
    // TODO limit number of bytes processed?
    for (i = 0; i < len; i++) {
        uint8_t val = bytequeue_get(&device->input_queue, 0);
        midi_process_byte(device, val);
        bytequeue_remove(&device->input_queue, 1);
    }
}