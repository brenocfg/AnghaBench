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
struct usb_interface_descriptor {int bNumEndpoints; } ;
struct usb_interface {struct usb_host_interface* altsetting; } ;
struct usb_host_interface {int* extra; int extralen; } ;
struct snd_usb_midi_endpoint_info {int in_cables; int out_cables; } ;
struct snd_usb_midi {struct usb_interface* iface; } ;

/* Variables and functions */
 int ENOENT ; 
 int UAC_MIDI_IN_JACK ; 
 int UAC_MIDI_OUT_JACK ; 
 int USB_DT_CS_INTERFACE ; 
 struct usb_interface_descriptor* get_iface_desc (struct usb_host_interface*) ; 
 int snd_usbmidi_detect_endpoints (struct snd_usb_midi*,struct snd_usb_midi_endpoint_info*,int) ; 

__attribute__((used)) static int snd_usbmidi_detect_yamaha(struct snd_usb_midi *umidi,
				     struct snd_usb_midi_endpoint_info *endpoint)
{
	struct usb_interface *intf;
	struct usb_host_interface *hostif;
	struct usb_interface_descriptor *intfd;
	uint8_t *cs_desc;

	intf = umidi->iface;
	if (!intf)
		return -ENOENT;
	hostif = intf->altsetting;
	intfd = get_iface_desc(hostif);
	if (intfd->bNumEndpoints < 1)
		return -ENOENT;

	/*
	 * For each port there is one MIDI_IN/OUT_JACK descriptor, not
	 * necessarily with any useful contents.  So simply count 'em.
	 */
	for (cs_desc = hostif->extra;
	     cs_desc < hostif->extra + hostif->extralen && cs_desc[0] >= 2;
	     cs_desc += cs_desc[0]) {
		if (cs_desc[1] == USB_DT_CS_INTERFACE) {
			if (cs_desc[2] == UAC_MIDI_IN_JACK)
				endpoint->in_cables =
					(endpoint->in_cables << 1) | 1;
			else if (cs_desc[2] == UAC_MIDI_OUT_JACK)
				endpoint->out_cables =
					(endpoint->out_cables << 1) | 1;
		}
	}
	if (!endpoint->in_cables && !endpoint->out_cables)
		return -ENOENT;

	return snd_usbmidi_detect_endpoints(umidi, endpoint, 1);
}