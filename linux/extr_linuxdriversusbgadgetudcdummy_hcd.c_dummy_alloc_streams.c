#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {TYPE_2__ desc; int /*<<< orphan*/  ss_ep_comp; } ;
struct usb_hcd {int dummy; } ;
struct usb_device {int dummy; } ;
struct dummy_hcd {int stream_en_ep; TYPE_1__* dum; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dummy_dev (struct dummy_hcd*) ; 
 unsigned int dummy_get_ep_idx (TYPE_2__*) ; 
 struct dummy_hcd* hcd_to_dummy_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  set_max_streams_for_pipe (struct dummy_hcd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_endpoint_num (TYPE_2__*) ; 
 int usb_ss_max_streams (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dummy_alloc_streams(struct usb_hcd *hcd, struct usb_device *udev,
	struct usb_host_endpoint **eps, unsigned int num_eps,
	unsigned int num_streams, gfp_t mem_flags)
{
	struct dummy_hcd *dum_hcd = hcd_to_dummy_hcd(hcd);
	unsigned long flags;
	int max_stream;
	int ret_streams = num_streams;
	unsigned int index;
	unsigned int i;

	if (!num_eps)
		return -EINVAL;

	spin_lock_irqsave(&dum_hcd->dum->lock, flags);
	for (i = 0; i < num_eps; i++) {
		index = dummy_get_ep_idx(&eps[i]->desc);
		if ((1 << index) & dum_hcd->stream_en_ep) {
			ret_streams = -EINVAL;
			goto out;
		}
		max_stream = usb_ss_max_streams(&eps[i]->ss_ep_comp);
		if (!max_stream) {
			ret_streams = -EINVAL;
			goto out;
		}
		if (max_stream < ret_streams) {
			dev_dbg(dummy_dev(dum_hcd), "Ep 0x%x only supports %u "
					"stream IDs.\n",
					eps[i]->desc.bEndpointAddress,
					max_stream);
			ret_streams = max_stream;
		}
	}

	for (i = 0; i < num_eps; i++) {
		index = dummy_get_ep_idx(&eps[i]->desc);
		dum_hcd->stream_en_ep |= 1 << index;
		set_max_streams_for_pipe(dum_hcd,
				usb_endpoint_num(&eps[i]->desc), ret_streams);
	}
out:
	spin_unlock_irqrestore(&dum_hcd->dum->lock, flags);
	return ret_streams;
}