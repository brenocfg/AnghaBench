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
struct snd_usb_midi_endpoint_info {int out_cables; int in_cables; scalar_t__ in_ep; scalar_t__ out_ep; } ;
struct snd_usb_midi {int dummy; } ;

/* Variables and functions */
 int MIDI_MAX_ENDPOINTS ; 
 int snd_usbmidi_detect_endpoints (struct snd_usb_midi*,struct snd_usb_midi_endpoint_info*,int) ; 

__attribute__((used)) static int snd_usbmidi_detect_per_port_endpoints(struct snd_usb_midi *umidi,
						 struct snd_usb_midi_endpoint_info *endpoints)
{
	int err, i;

	err = snd_usbmidi_detect_endpoints(umidi, endpoints, MIDI_MAX_ENDPOINTS);
	for (i = 0; i < MIDI_MAX_ENDPOINTS; ++i) {
		if (endpoints[i].out_ep)
			endpoints[i].out_cables = 0x0001;
		if (endpoints[i].in_ep)
			endpoints[i].in_cables = 0x0001;
	}
	return err;
}