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
struct usbhsh_hpriv {int dummy; } ;
struct usbhs_pkt {scalar_t__ zero; } ;
struct urb {int actual_length; int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; TYPE_1__* ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_dotoggle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_endpoint_maxp (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_pipecontrol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbhsh_endpoint_sequence_save(struct usbhsh_hpriv *hpriv,
					  struct urb *urb,
					  struct usbhs_pkt *pkt)
{
	int len = urb->actual_length;
	int maxp = usb_endpoint_maxp(&urb->ep->desc);
	int t = 0;

	/* DCP is out of sequence control */
	if (usb_pipecontrol(urb->pipe))
		return;

	/*
	 * renesas_usbhs pipe has a limitation in a number.
	 * So, driver should re-use the limited pipe for each device/endpoint.
	 * DATA0/1 sequence should be saved for it.
	 * see [image of mod_host]
	 *     [HARDWARE LIMITATION]
	 */

	/*
	 * next sequence depends on actual_length
	 *
	 * ex) actual_length = 1147, maxp = 512
	 * data0 : 512
	 * data1 : 512
	 * data0 : 123
	 * data1 is the next sequence
	 */
	t = len / maxp;
	if (len % maxp)
		t++;
	if (pkt->zero)
		t++;
	t %= 2;

	if (t)
		usb_dotoggle(urb->dev,
			     usb_pipeendpoint(urb->pipe),
			     usb_pipeout(urb->pipe));
}