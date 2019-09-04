#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wahc {int /*<<< orphan*/  rpipe_mutex; TYPE_1__* usb_iface; } ;
struct TYPE_6__ {int /*<<< orphan*/  wRPipeIndex; } ;
struct wa_rpipe {TYPE_3__ descr; struct usb_host_endpoint* ep; } ;
struct TYPE_5__ {int bmAttributes; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {TYPE_2__ desc; struct wa_rpipe* hcpriv; } ;
struct urb {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int CONFIG_BUG ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  __rpipe_get (struct wa_rpipe*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpipe_aim (struct wa_rpipe*,struct wahc*,struct usb_host_endpoint*,struct urb*,int /*<<< orphan*/ ) ; 
 int rpipe_check_aim (struct wa_rpipe*,struct wahc*,struct usb_host_endpoint*,struct urb*,int /*<<< orphan*/ ) ; 
 int rpipe_get_idle (struct wa_rpipe**,struct wahc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpipe_put (struct wa_rpipe*) ; 

int rpipe_get_by_ep(struct wahc *wa, struct usb_host_endpoint *ep,
		    struct urb *urb, gfp_t gfp)
{
	int result = 0;
	struct device *dev = &wa->usb_iface->dev;
	struct wa_rpipe *rpipe;
	u8 eptype;

	mutex_lock(&wa->rpipe_mutex);
	rpipe = ep->hcpriv;
	if (rpipe != NULL) {
		if (CONFIG_BUG == 1) {
			result = rpipe_check_aim(rpipe, wa, ep, urb, gfp);
			if (result < 0)
				goto error;
		}
		__rpipe_get(rpipe);
		dev_dbg(dev, "ep 0x%02x: reusing rpipe %u\n",
			ep->desc.bEndpointAddress,
			le16_to_cpu(rpipe->descr.wRPipeIndex));
	} else {
		/* hmm, assign idle rpipe, aim it */
		result = -ENOBUFS;
		eptype = ep->desc.bmAttributes & 0x03;
		result = rpipe_get_idle(&rpipe, wa, 1 << eptype, gfp);
		if (result < 0)
			goto error;
		result = rpipe_aim(rpipe, wa, ep, urb, gfp);
		if (result < 0) {
			rpipe_put(rpipe);
			goto error;
		}
		ep->hcpriv = rpipe;
		rpipe->ep = ep;
		__rpipe_get(rpipe);	/* for caching into ep->hcpriv */
		dev_dbg(dev, "ep 0x%02x: using rpipe %u\n",
			ep->desc.bEndpointAddress,
			le16_to_cpu(rpipe->descr.wRPipeIndex));
	}
error:
	mutex_unlock(&wa->rpipe_mutex);
	return result;
}