#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_ms_header_descriptor {int bLength; scalar_t__ bDescriptorType; scalar_t__ bDescriptorSubtype; int* bcdMSC; } ;
struct usb_ms_endpoint_descriptor {int bLength; scalar_t__ bDescriptorType; scalar_t__ bDescriptorSubtype; int bNumEmbMIDIJack; } ;
struct usb_interface_descriptor {int bNumEndpoints; } ;
struct usb_interface {struct usb_host_interface* altsetting; } ;
struct usb_host_interface {int extralen; struct usb_host_endpoint* endpoint; scalar_t__ extra; } ;
struct usb_host_endpoint {int extralen; scalar_t__ extra; } ;
struct usb_endpoint_descriptor {int bInterval; int bEndpointAddress; } ;
struct snd_usb_midi_endpoint_info {int out_interval; int out_cables; int in_interval; int in_cables; void* in_ep; void* out_ep; } ;
struct snd_usb_midi {TYPE_1__* dev; struct usb_interface* iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int MIDI_MAX_ENDPOINTS ; 
 scalar_t__ UAC_HEADER ; 
 scalar_t__ UAC_MS_GENERAL ; 
 scalar_t__ USB_DT_CS_ENDPOINT ; 
 scalar_t__ USB_DT_CS_INTERFACE ; 
 scalar_t__ USB_SPEED_LOW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct usb_endpoint_descriptor* get_ep_desc (struct usb_host_endpoint*) ; 
 struct usb_interface_descriptor* get_iface_desc (struct usb_host_interface*) ; 
 scalar_t__ snd_usb_get_speed (TYPE_1__*) ; 
 scalar_t__ usb_endpoint_dir_out (struct usb_endpoint_descriptor*) ; 
 void* usb_endpoint_num (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_bulk (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_xfer_int (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static int snd_usbmidi_get_ms_info(struct snd_usb_midi *umidi,
				   struct snd_usb_midi_endpoint_info *endpoints)
{
	struct usb_interface *intf;
	struct usb_host_interface *hostif;
	struct usb_interface_descriptor *intfd;
	struct usb_ms_header_descriptor *ms_header;
	struct usb_host_endpoint *hostep;
	struct usb_endpoint_descriptor *ep;
	struct usb_ms_endpoint_descriptor *ms_ep;
	int i, epidx;

	intf = umidi->iface;
	if (!intf)
		return -ENXIO;
	hostif = &intf->altsetting[0];
	intfd = get_iface_desc(hostif);
	ms_header = (struct usb_ms_header_descriptor *)hostif->extra;
	if (hostif->extralen >= 7 &&
	    ms_header->bLength >= 7 &&
	    ms_header->bDescriptorType == USB_DT_CS_INTERFACE &&
	    ms_header->bDescriptorSubtype == UAC_HEADER)
		dev_dbg(&umidi->dev->dev, "MIDIStreaming version %02x.%02x\n",
			    ms_header->bcdMSC[1], ms_header->bcdMSC[0]);
	else
		dev_warn(&umidi->dev->dev,
			 "MIDIStreaming interface descriptor not found\n");

	epidx = 0;
	for (i = 0; i < intfd->bNumEndpoints; ++i) {
		hostep = &hostif->endpoint[i];
		ep = get_ep_desc(hostep);
		if (!usb_endpoint_xfer_bulk(ep) && !usb_endpoint_xfer_int(ep))
			continue;
		ms_ep = (struct usb_ms_endpoint_descriptor *)hostep->extra;
		if (hostep->extralen < 4 ||
		    ms_ep->bLength < 4 ||
		    ms_ep->bDescriptorType != USB_DT_CS_ENDPOINT ||
		    ms_ep->bDescriptorSubtype != UAC_MS_GENERAL)
			continue;
		if (usb_endpoint_dir_out(ep)) {
			if (endpoints[epidx].out_ep) {
				if (++epidx >= MIDI_MAX_ENDPOINTS) {
					dev_warn(&umidi->dev->dev,
						 "too many endpoints\n");
					break;
				}
			}
			endpoints[epidx].out_ep = usb_endpoint_num(ep);
			if (usb_endpoint_xfer_int(ep))
				endpoints[epidx].out_interval = ep->bInterval;
			else if (snd_usb_get_speed(umidi->dev) == USB_SPEED_LOW)
				/*
				 * Low speed bulk transfers don't exist, so
				 * force interrupt transfers for devices like
				 * ESI MIDI Mate that try to use them anyway.
				 */
				endpoints[epidx].out_interval = 1;
			endpoints[epidx].out_cables =
				(1 << ms_ep->bNumEmbMIDIJack) - 1;
			dev_dbg(&umidi->dev->dev, "EP %02X: %d jack(s)\n",
				ep->bEndpointAddress, ms_ep->bNumEmbMIDIJack);
		} else {
			if (endpoints[epidx].in_ep) {
				if (++epidx >= MIDI_MAX_ENDPOINTS) {
					dev_warn(&umidi->dev->dev,
						 "too many endpoints\n");
					break;
				}
			}
			endpoints[epidx].in_ep = usb_endpoint_num(ep);
			if (usb_endpoint_xfer_int(ep))
				endpoints[epidx].in_interval = ep->bInterval;
			else if (snd_usb_get_speed(umidi->dev) == USB_SPEED_LOW)
				endpoints[epidx].in_interval = 1;
			endpoints[epidx].in_cables =
				(1 << ms_ep->bNumEmbMIDIJack) - 1;
			dev_dbg(&umidi->dev->dev, "EP %02X: %d jack(s)\n",
				ep->bEndpointAddress, ms_ep->bNumEmbMIDIJack);
		}
	}
	return 0;
}