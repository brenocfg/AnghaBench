#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  (* midi_two_byte_func_t ) (TYPE_1__*,int,int) ;
typedef  int /*<<< orphan*/  (* midi_three_byte_func_t ) (TYPE_1__*,int,int,int) ;
typedef  int /*<<< orphan*/  (* midi_one_byte_func_t ) (TYPE_1__*,int) ;
struct TYPE_9__ {scalar_t__ input_state; int /*<<< orphan*/  (* input_catchall_callback ) (TYPE_1__*,int,int,int,int) ;int /*<<< orphan*/  (* input_fallthrough_callback ) (TYPE_1__*,int,int,int,int) ;int /*<<< orphan*/  (* input_tunerequest_callback ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* input_realtime_callback ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* input_tc_quarterframe_callback ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* input_songselect_callback ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* input_chanpressure_callback ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* input_progchange_callback ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* input_songposition_callback ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* input_pitchbend_callback ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* input_aftertouch_callback ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* input_noteoff_callback ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* input_noteon_callback ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* input_cc_callback ) (TYPE_1__*,int,int,int) ;int /*<<< orphan*/  (* input_sysex_callback ) (TYPE_1__*,int const,int const,int*) ;} ;
typedef  TYPE_1__ MidiDevice ;

/* Variables and functions */
#define  MIDI_AFTERTOUCH 134 
#define  MIDI_CC 133 
#define  MIDI_CHANPRESSURE 132 
#define  MIDI_NOTEOFF 131 
#define  MIDI_NOTEON 130 
#define  MIDI_PITCHBEND 129 
#define  MIDI_PROGCHANGE 128 
 int MIDI_SONGPOSITION ; 
 int MIDI_SONGSELECT ; 
 int MIDI_TC_QUARTERFRAME ; 
 int MIDI_TUNEREQUEST ; 
 scalar_t__ SYSEX_MESSAGE ; 
 int /*<<< orphan*/  midi_is_realtime (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int const,int const,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int,int,int,int) ; 

void midi_input_callbacks(MidiDevice* device, uint16_t cnt, uint8_t byte0, uint8_t byte1, uint8_t byte2) {
    // did we end up calling a callback?
    bool called = false;
    if (device->input_state == SYSEX_MESSAGE) {
        if (device->input_sysex_callback) {
            const uint16_t start  = ((cnt - 1) / 3) * 3;
            const uint8_t  length = (cnt - start);
            uint8_t        data[3];
            data[0] = byte0;
            data[1] = byte1;
            data[2] = byte2;
            device->input_sysex_callback(device, start, length, data);
            called = true;
        }
    } else {
        switch (cnt) {
            case 3: {
                midi_three_byte_func_t func = NULL;
                switch (byte0 & 0xF0) {
                    case MIDI_CC:
                        func = device->input_cc_callback;
                        break;
                    case MIDI_NOTEON:
                        func = device->input_noteon_callback;
                        break;
                    case MIDI_NOTEOFF:
                        func = device->input_noteoff_callback;
                        break;
                    case MIDI_AFTERTOUCH:
                        func = device->input_aftertouch_callback;
                        break;
                    case MIDI_PITCHBEND:
                        func = device->input_pitchbend_callback;
                        break;
                    case 0xF0:
                        if (byte0 == MIDI_SONGPOSITION) func = device->input_songposition_callback;
                        break;
                    default:
                        break;
                }
                if (func) {
                    // mask off the channel for non song position functions
                    if (byte0 == MIDI_SONGPOSITION)
                        func(device, byte0, byte1, byte2);
                    else
                        func(device, byte0 & 0x0F, byte1, byte2);
                    called = true;
                }
            } break;
            case 2: {
                midi_two_byte_func_t func = NULL;
                switch (byte0 & 0xF0) {
                    case MIDI_PROGCHANGE:
                        func = device->input_progchange_callback;
                        break;
                    case MIDI_CHANPRESSURE:
                        func = device->input_chanpressure_callback;
                        break;
                    case 0xF0:
                        if (byte0 == MIDI_SONGSELECT)
                            func = device->input_songselect_callback;
                        else if (byte0 == MIDI_TC_QUARTERFRAME)
                            func = device->input_tc_quarterframe_callback;
                        break;
                    default:
                        break;
                }
                if (func) {
                    // mask off the channel
                    if (byte0 == MIDI_SONGSELECT || byte0 == MIDI_TC_QUARTERFRAME)
                        func(device, byte0, byte1);
                    else
                        func(device, byte0 & 0x0F, byte1);
                    called = true;
                }
            } break;
            case 1: {
                midi_one_byte_func_t func = NULL;
                if (midi_is_realtime(byte0))
                    func = device->input_realtime_callback;
                else if (byte0 == MIDI_TUNEREQUEST)
                    func = device->input_tunerequest_callback;
                if (func) {
                    func(device, byte0);
                    called = true;
                }
            } break;
            default:
                // just in case
                if (cnt > 3) cnt = 0;
                break;
        }
    }

    // if there is fallthrough default callback and we haven't called a more specific one,
    // call the fallthrough
    if (!called && device->input_fallthrough_callback) device->input_fallthrough_callback(device, cnt, byte0, byte1, byte2);
    // always call the catch all if it exists
    if (device->input_catchall_callback) device->input_catchall_callback(device, cnt, byte0, byte1, byte2);
}