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
struct snd_usb_endpoint {scalar_t__ type; int skip_packets; int syncmaxsize; int tenor_fb_quirk; TYPE_1__* chip; } ;
struct TYPE_2__ {scalar_t__ usb_id; } ;

/* Variables and functions */
 scalar_t__ SND_USB_ENDPOINT_TYPE_DATA ; 
 scalar_t__ SND_USB_ENDPOINT_TYPE_SYNC ; 
 scalar_t__ USB_ID (int,int) ; 
 int USB_ID_VENDOR (scalar_t__) ; 

void snd_usb_endpoint_start_quirk(struct snd_usb_endpoint *ep)
{
	/*
	 * "Playback Design" products send bogus feedback data at the start
	 * of the stream. Ignore them.
	 */
	if (USB_ID_VENDOR(ep->chip->usb_id) == 0x23ba &&
	    ep->type == SND_USB_ENDPOINT_TYPE_SYNC)
		ep->skip_packets = 4;

	/*
	 * M-Audio Fast Track C400/C600 - when packets are not skipped, real
	 * world latency varies by approx. +/- 50 frames (at 96KHz) each time
	 * the stream is (re)started. When skipping packets 16 at endpoint
	 * start up, the real world latency is stable within +/- 1 frame (also
	 * across power cycles).
	 */
	if ((ep->chip->usb_id == USB_ID(0x0763, 0x2030) ||
	     ep->chip->usb_id == USB_ID(0x0763, 0x2031)) &&
	    ep->type == SND_USB_ENDPOINT_TYPE_DATA)
		ep->skip_packets = 16;

	/* Work around devices that report unreasonable feedback data */
	if ((ep->chip->usb_id == USB_ID(0x0644, 0x8038) ||  /* TEAC UD-H01 */
	     ep->chip->usb_id == USB_ID(0x1852, 0x5034)) && /* T+A Dac8 */
	    ep->syncmaxsize == 4)
		ep->tenor_fb_quirk = 1;
}