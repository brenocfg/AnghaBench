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
struct TYPE_4__ {int /*<<< orphan*/  (* send_func ) (TYPE_1__*,int,int,int,int) ;} ;
typedef  TYPE_1__ MidiDevice ;

/* Variables and functions */
 int MIDI_AFTERTOUCH ; 
 int MIDI_CHANMASK ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int,int,int) ; 

void midi_send_aftertouch(MidiDevice* device, uint8_t chan, uint8_t note_num, uint8_t amt) { device->send_func(device, 3, MIDI_AFTERTOUCH | (chan & MIDI_CHANMASK), note_num & 0x7F, amt & 0x7F); }