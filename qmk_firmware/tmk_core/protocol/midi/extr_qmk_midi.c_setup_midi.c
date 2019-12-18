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

/* Variables and functions */
 int /*<<< orphan*/  cc_callback ; 
 int /*<<< orphan*/  fallthrough_callback ; 
 int /*<<< orphan*/  midi_device ; 
 int /*<<< orphan*/  midi_device_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  midi_device_set_pre_input_process_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  midi_device_set_send_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  midi_init () ; 
 int /*<<< orphan*/  midi_register_cc_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  midi_register_fallthrough_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  midi_register_sysex_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysex_callback ; 
 int /*<<< orphan*/  usb_get_midi ; 
 int /*<<< orphan*/  usb_send_func ; 

void setup_midi(void) {
#ifdef MIDI_ADVANCED
    midi_init();
#endif
    midi_device_init(&midi_device);
    midi_device_set_send_func(&midi_device, usb_send_func);
    midi_device_set_pre_input_process_func(&midi_device, usb_get_midi);
    midi_register_fallthrough_callback(&midi_device, fallthrough_callback);
    midi_register_cc_callback(&midi_device, cc_callback);
#ifdef API_SYSEX_ENABLE
    midi_register_sysex_callback(&midi_device, sysex_callback);
#endif
}