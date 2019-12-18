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
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* send_func ) (TYPE_1__*,int,int /*<<< orphan*/ ,int,int) ;} ;
typedef  TYPE_1__ MidiDevice ;

/* Variables and functions */
 int /*<<< orphan*/  MIDI_SONGPOSITION ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int /*<<< orphan*/ ,int,int) ; 

void midi_send_songposition(MidiDevice* device, uint16_t pos) { device->send_func(device, 3, MIDI_SONGPOSITION, pos & 0x7F, (pos >> 7) & 0x7F); }