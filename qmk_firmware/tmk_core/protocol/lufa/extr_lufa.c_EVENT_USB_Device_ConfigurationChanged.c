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
 int /*<<< orphan*/  CDC_EPSIZE ; 
 int /*<<< orphan*/  CDC_IN_EPADDR ; 
 int /*<<< orphan*/  CDC_NOTIFICATION_EPADDR ; 
 int /*<<< orphan*/  CDC_NOTIFICATION_EPSIZE ; 
 int /*<<< orphan*/  CDC_OUT_EPADDR ; 
 int /*<<< orphan*/  CONSOLE_EPSIZE ; 
 int /*<<< orphan*/  CONSOLE_IN_EPNUM ; 
 int /*<<< orphan*/  CONSOLE_OUT_EPNUM ; 
 int /*<<< orphan*/  ENDPOINT_BANK_SINGLE ; 
 int ENDPOINT_CONFIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENDPOINT_DIR_IN ; 
 int /*<<< orphan*/  ENDPOINT_DIR_OUT ; 
 int /*<<< orphan*/  EP_TYPE_BULK ; 
 int /*<<< orphan*/  EP_TYPE_INTERRUPT ; 
 int Endpoint_ConfigureEndpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEYBOARD_EPSIZE ; 
 int /*<<< orphan*/  KEYBOARD_IN_EPNUM ; 
 int /*<<< orphan*/  MIDI_STREAM_EPSIZE ; 
 int /*<<< orphan*/  MIDI_STREAM_IN_EPADDR ; 
 int /*<<< orphan*/  MIDI_STREAM_OUT_EPADDR ; 
 int /*<<< orphan*/  MOUSE_EPSIZE ; 
 int /*<<< orphan*/  MOUSE_IN_EPNUM ; 
 int /*<<< orphan*/  RAW_EPSIZE ; 
 int /*<<< orphan*/  RAW_IN_EPNUM ; 
 int /*<<< orphan*/  RAW_OUT_EPNUM ; 
 int /*<<< orphan*/  SHARED_EPSIZE ; 
 int /*<<< orphan*/  SHARED_IN_EPNUM ; 

void EVENT_USB_Device_ConfigurationChanged(void) {
    bool ConfigSuccess = true;

    /* Setup Keyboard HID Report Endpoints */
#ifndef KEYBOARD_SHARED_EP
    ConfigSuccess &= ENDPOINT_CONFIG(KEYBOARD_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN, KEYBOARD_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

#if defined(MOUSE_ENABLE) && !defined(MOUSE_SHARED_EP)
    /* Setup Mouse HID Report Endpoint */
    ConfigSuccess &= ENDPOINT_CONFIG(MOUSE_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN, MOUSE_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

#ifdef SHARED_EP_ENABLE
    /* Setup Shared HID Report Endpoint */
    ConfigSuccess &= ENDPOINT_CONFIG(SHARED_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN, SHARED_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

#ifdef RAW_ENABLE
    /* Setup Raw HID Report Endpoints */
    ConfigSuccess &= ENDPOINT_CONFIG(RAW_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN, RAW_EPSIZE, ENDPOINT_BANK_SINGLE);
    ConfigSuccess &= ENDPOINT_CONFIG(RAW_OUT_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_OUT, RAW_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

#ifdef CONSOLE_ENABLE
    /* Setup Console HID Report Endpoints */
    ConfigSuccess &= ENDPOINT_CONFIG(CONSOLE_IN_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_IN, CONSOLE_EPSIZE, ENDPOINT_BANK_SINGLE);
#    if 0
    ConfigSuccess &= ENDPOINT_CONFIG(CONSOLE_OUT_EPNUM, EP_TYPE_INTERRUPT, ENDPOINT_DIR_OUT,
                                     CONSOLE_EPSIZE, ENDPOINT_BANK_SINGLE);
#    endif
#endif

#ifdef MIDI_ENABLE
    ConfigSuccess &= Endpoint_ConfigureEndpoint(MIDI_STREAM_IN_EPADDR, EP_TYPE_BULK, MIDI_STREAM_EPSIZE, ENDPOINT_BANK_SINGLE);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(MIDI_STREAM_OUT_EPADDR, EP_TYPE_BULK, MIDI_STREAM_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif

#ifdef VIRTSER_ENABLE
    ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_NOTIFICATION_EPADDR, EP_TYPE_INTERRUPT, CDC_NOTIFICATION_EPSIZE, ENDPOINT_BANK_SINGLE);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_OUT_EPADDR, EP_TYPE_BULK, CDC_EPSIZE, ENDPOINT_BANK_SINGLE);
    ConfigSuccess &= Endpoint_ConfigureEndpoint(CDC_IN_EPADDR, EP_TYPE_BULK, CDC_EPSIZE, ENDPOINT_BANK_SINGLE);
#endif
}