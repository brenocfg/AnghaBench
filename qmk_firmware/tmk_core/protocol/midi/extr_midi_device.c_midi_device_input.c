#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  input_queue; } ;
typedef  TYPE_1__ MidiDevice ;

/* Variables and functions */
 int /*<<< orphan*/  bytequeue_enqueue (int /*<<< orphan*/ *,size_t) ; 

void midi_device_input(MidiDevice* device, uint8_t cnt, uint8_t* input) {
    uint8_t i;
    for (i = 0; i < cnt; i++) bytequeue_enqueue(&device->input_queue, input[i]);
}