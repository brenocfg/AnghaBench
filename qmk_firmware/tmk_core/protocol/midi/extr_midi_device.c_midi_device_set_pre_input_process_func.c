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
typedef  int /*<<< orphan*/  midi_no_byte_func_t ;
struct TYPE_3__ {int /*<<< orphan*/  pre_input_process_callback; } ;
typedef  TYPE_1__ MidiDevice ;

/* Variables and functions */

void midi_device_set_pre_input_process_func(MidiDevice* device, midi_no_byte_func_t pre_process_func) { device->pre_input_process_callback = pre_process_func; }