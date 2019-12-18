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
struct TYPE_4__ {int /*<<< orphan*/  (* send_func ) (TYPE_1__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ MidiDevice ;

/* Variables and functions */
 int /*<<< orphan*/  MIDI_SONGSELECT ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void midi_send_songselect(MidiDevice* device, uint8_t song) { device->send_func(device, 2, MIDI_SONGSELECT, song & 0x7F, 0); }