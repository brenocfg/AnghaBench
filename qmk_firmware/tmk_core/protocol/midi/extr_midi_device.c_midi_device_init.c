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
struct TYPE_3__ {int /*<<< orphan*/ * pre_input_process_callback; int /*<<< orphan*/ * input_catchall_callback; int /*<<< orphan*/ * input_fallthrough_callback; int /*<<< orphan*/ * input_sysex_callback; int /*<<< orphan*/ * input_tunerequest_callback; int /*<<< orphan*/ * input_realtime_callback; int /*<<< orphan*/ * input_tc_quarterframe_callback; int /*<<< orphan*/ * input_songselect_callback; int /*<<< orphan*/ * input_chanpressure_callback; int /*<<< orphan*/ * input_progchange_callback; int /*<<< orphan*/ * input_songposition_callback; int /*<<< orphan*/ * input_pitchbend_callback; int /*<<< orphan*/ * input_aftertouch_callback; int /*<<< orphan*/ * input_noteoff_callback; int /*<<< orphan*/ * input_noteon_callback; int /*<<< orphan*/ * input_cc_callback; int /*<<< orphan*/  input_queue_data; int /*<<< orphan*/  input_queue; scalar_t__ input_count; int /*<<< orphan*/  input_state; } ;
typedef  TYPE_1__ MidiDevice ;

/* Variables and functions */
 int /*<<< orphan*/  IDLE ; 
 int /*<<< orphan*/  MIDI_INPUT_QUEUE_LENGTH ; 
 int /*<<< orphan*/  bytequeue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void midi_device_init(MidiDevice* device) {
    device->input_state = IDLE;
    device->input_count = 0;
    bytequeue_init(&device->input_queue, device->input_queue_data, MIDI_INPUT_QUEUE_LENGTH);

    // three byte funcs
    device->input_cc_callback           = NULL;
    device->input_noteon_callback       = NULL;
    device->input_noteoff_callback      = NULL;
    device->input_aftertouch_callback   = NULL;
    device->input_pitchbend_callback    = NULL;
    device->input_songposition_callback = NULL;

    // two byte funcs
    device->input_progchange_callback      = NULL;
    device->input_chanpressure_callback    = NULL;
    device->input_songselect_callback      = NULL;
    device->input_tc_quarterframe_callback = NULL;

    // one byte funcs
    device->input_realtime_callback    = NULL;
    device->input_tunerequest_callback = NULL;

    // var byte functions
    device->input_sysex_callback       = NULL;
    device->input_fallthrough_callback = NULL;
    device->input_catchall_callback    = NULL;

    device->pre_input_process_callback = NULL;
}