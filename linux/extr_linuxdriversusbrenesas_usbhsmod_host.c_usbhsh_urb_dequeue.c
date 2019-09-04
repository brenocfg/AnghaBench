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
struct usbhs_pkt {int /*<<< orphan*/  pipe; } ;
struct usbhsh_request {struct usbhs_pkt pkt; } ;
struct usbhsh_hpriv {int dummy; } ;
struct usbhs_priv {int dummy; } ;
struct usb_hcd {int dummy; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usbhs_pkt_pop (int /*<<< orphan*/ ,struct usbhs_pkt*) ; 
 struct usbhsh_hpriv* usbhsh_hcd_to_hpriv (struct usb_hcd*) ; 
 struct usbhs_priv* usbhsh_hpriv_to_priv (struct usbhsh_hpriv*) ; 
 int /*<<< orphan*/  usbhsh_queue_done (struct usbhs_priv*,struct usbhs_pkt*) ; 
 struct usbhsh_request* usbhsh_urb_to_ureq (struct urb*) ; 

__attribute__((used)) static int usbhsh_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct usbhsh_hpriv *hpriv = usbhsh_hcd_to_hpriv(hcd);
	struct usbhsh_request *ureq = usbhsh_urb_to_ureq(urb);

	if (ureq) {
		struct usbhs_priv *priv = usbhsh_hpriv_to_priv(hpriv);
		struct usbhs_pkt *pkt = &ureq->pkt;

		usbhs_pkt_pop(pkt->pipe, pkt);
		usbhsh_queue_done(priv, pkt);
	}

	return 0;
}