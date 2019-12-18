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
struct snd_usb_substream {scalar_t__ speed; } ;
struct snd_usb_endpoint {int freqm; int freqshift; int syncmaxsize; int /*<<< orphan*/  curpacksize; } ;
struct snd_info_buffer {int dummy; } ;

/* Variables and functions */
 int INT_MIN ; 
 scalar_t__ USB_SPEED_FULL ; 
 int /*<<< orphan*/  get_full_speed_hz (int) ; 
 int /*<<< orphan*/  get_high_speed_hz (int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int,...) ; 

__attribute__((used)) static void proc_dump_ep_status(struct snd_usb_substream *subs,
				struct snd_usb_endpoint *data_ep,
				struct snd_usb_endpoint *sync_ep,
				struct snd_info_buffer *buffer)
{
	if (!data_ep)
		return;
	snd_iprintf(buffer, "    Packet Size = %d\n", data_ep->curpacksize);
	snd_iprintf(buffer, "    Momentary freq = %u Hz (%#x.%04x)\n",
		    subs->speed == USB_SPEED_FULL
		    ? get_full_speed_hz(data_ep->freqm)
		    : get_high_speed_hz(data_ep->freqm),
		    data_ep->freqm >> 16, data_ep->freqm & 0xffff);
	if (sync_ep && data_ep->freqshift != INT_MIN) {
		int res = 16 - data_ep->freqshift;
		snd_iprintf(buffer, "    Feedback Format = %d.%d\n",
			    (sync_ep->syncmaxsize > 3 ? 32 : 24) - res, res);
	}
}