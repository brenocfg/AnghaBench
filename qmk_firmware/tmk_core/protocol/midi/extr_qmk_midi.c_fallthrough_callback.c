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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  MidiDevice ;

/* Variables and functions */
#define  MIDI_NOTEOFF 129 
#define  MIDI_NOTEON 128 
 int MIDI_STOP ; 
 int /*<<< orphan*/  play_note (double,int) ; 
 double pow (double,int) ; 
 int /*<<< orphan*/  stop_all_notes () ; 
 int /*<<< orphan*/  stop_note (double) ; 

__attribute__((used)) static void fallthrough_callback(MidiDevice* device, uint16_t cnt, uint8_t byte0, uint8_t byte1, uint8_t byte2) {
#ifdef AUDIO_ENABLE
    if (cnt == 3) {
        switch (byte0 & 0xF0) {
            case MIDI_NOTEON:
                play_note(((double)261.6) * pow(2.0, -4.0) * pow(2.0, (byte1 & 0x7F) / 12.0), (byte2 & 0x7F) / 8);
                break;
            case MIDI_NOTEOFF:
                stop_note(((double)261.6) * pow(2.0, -4.0) * pow(2.0, (byte1 & 0x7F) / 12.0));
                break;
        }
    }
    if (byte0 == MIDI_STOP) {
        stop_all_notes();
    }
#endif
}