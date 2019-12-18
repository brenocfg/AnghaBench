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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  midi_packet_length_t ;

/* Variables and functions */
#define  MIDI_ACTIVESENSE 147 
#define  MIDI_AFTERTOUCH 146 
#define  MIDI_CC 145 
#define  MIDI_CHANPRESSURE 144 
#define  MIDI_CLOCK 143 
#define  MIDI_CONTINUE 142 
#define  MIDI_NOTEOFF 141 
#define  MIDI_NOTEON 140 
#define  MIDI_PITCHBEND 139 
#define  MIDI_PROGCHANGE 138 
#define  MIDI_RESET 137 
#define  MIDI_SONGPOSITION 136 
#define  MIDI_SONGSELECT 135 
#define  MIDI_START 134 
#define  MIDI_STOP 133 
#define  MIDI_TC_QUARTERFRAME 132 
#define  MIDI_TICK 131 
#define  MIDI_TUNEREQUEST 130 
 int /*<<< orphan*/  ONE ; 
#define  SYSEX_BEGIN 129 
#define  SYSEX_END 128 
 int /*<<< orphan*/  THREE ; 
 int /*<<< orphan*/  TWO ; 
 int /*<<< orphan*/  UNDEFINED ; 

midi_packet_length_t midi_packet_length(uint8_t status) {
    switch (status & 0xF0) {
        case MIDI_CC:
        case MIDI_NOTEON:
        case MIDI_NOTEOFF:
        case MIDI_AFTERTOUCH:
        case MIDI_PITCHBEND:
            return THREE;
        case MIDI_PROGCHANGE:
        case MIDI_CHANPRESSURE:
        case MIDI_SONGSELECT:
            return TWO;
        case 0xF0:
            switch (status) {
                case MIDI_CLOCK:
                case MIDI_TICK:
                case MIDI_START:
                case MIDI_CONTINUE:
                case MIDI_STOP:
                case MIDI_ACTIVESENSE:
                case MIDI_RESET:
                case MIDI_TUNEREQUEST:
                    return ONE;
                case MIDI_SONGPOSITION:
                    return THREE;
                case MIDI_TC_QUARTERFRAME:
                case MIDI_SONGSELECT:
                    return TWO;
                case SYSEX_END:
                case SYSEX_BEGIN:
                default:
                    return UNDEFINED;
            }
        default:
            return UNDEFINED;
    }
}