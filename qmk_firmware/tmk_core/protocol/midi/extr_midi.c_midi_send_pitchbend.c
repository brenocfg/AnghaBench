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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int int16_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* send_func ) (TYPE_1__*,int,int,int,int) ;} ;
typedef  TYPE_1__ MidiDevice ;

/* Variables and functions */
 int MIDI_CHANMASK ; 
 int MIDI_PITCHBEND ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int,int,int) ; 

void midi_send_pitchbend(MidiDevice* device, uint8_t chan, int16_t amt) {
    uint16_t uAmt;
    // check range
    if (amt > 0x1fff) {
        uAmt = 0x3FFF;
    } else if (amt < -0x2000) {
        uAmt = 0;
    } else {
        uAmt = amt + 0x2000;
    }
    device->send_func(device, 3, MIDI_PITCHBEND | (chan & MIDI_CHANMASK), uAmt & 0x7F, (uAmt >> 7) & 0x7F);
}