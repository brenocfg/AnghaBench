#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_ep {struct f_sourcesink* driver_data; } ;
struct usb_composite_dev {TYPE_1__* gadget; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct f_sourcesink {int cur_alt; TYPE_2__ function; struct usb_ep* iso_out_ep; struct usb_ep* iso_in_ep; struct usb_ep* out_ep; struct usb_ep* in_ep; } ;
struct TYPE_3__ {int speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int config_ep_by_speed (TYPE_1__*,TYPE_2__*,struct usb_ep*) ; 
 int source_sink_start_ep (struct f_sourcesink*,int,int,int) ; 
 int /*<<< orphan*/  usb_ep_disable (struct usb_ep*) ; 
 int usb_ep_enable (struct usb_ep*) ; 

__attribute__((used)) static int
enable_source_sink(struct usb_composite_dev *cdev, struct f_sourcesink *ss,
		int alt)
{
	int					result = 0;
	int					speed = cdev->gadget->speed;
	struct usb_ep				*ep;

	/* one bulk endpoint writes (sources) zeroes IN (to the host) */
	ep = ss->in_ep;
	result = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
	if (result)
		return result;
	result = usb_ep_enable(ep);
	if (result < 0)
		return result;
	ep->driver_data = ss;

	result = source_sink_start_ep(ss, true, false, speed);
	if (result < 0) {
fail:
		ep = ss->in_ep;
		usb_ep_disable(ep);
		return result;
	}

	/* one bulk endpoint reads (sinks) anything OUT (from the host) */
	ep = ss->out_ep;
	result = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
	if (result)
		goto fail;
	result = usb_ep_enable(ep);
	if (result < 0)
		goto fail;
	ep->driver_data = ss;

	result = source_sink_start_ep(ss, false, false, speed);
	if (result < 0) {
fail2:
		ep = ss->out_ep;
		usb_ep_disable(ep);
		goto fail;
	}

	if (alt == 0)
		goto out;

	/* one iso endpoint writes (sources) zeroes IN (to the host) */
	ep = ss->iso_in_ep;
	if (ep) {
		result = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
		if (result)
			goto fail2;
		result = usb_ep_enable(ep);
		if (result < 0)
			goto fail2;
		ep->driver_data = ss;

		result = source_sink_start_ep(ss, true, true, speed);
		if (result < 0) {
fail3:
			ep = ss->iso_in_ep;
			if (ep)
				usb_ep_disable(ep);
			goto fail2;
		}
	}

	/* one iso endpoint reads (sinks) anything OUT (from the host) */
	ep = ss->iso_out_ep;
	if (ep) {
		result = config_ep_by_speed(cdev->gadget, &(ss->function), ep);
		if (result)
			goto fail3;
		result = usb_ep_enable(ep);
		if (result < 0)
			goto fail3;
		ep->driver_data = ss;

		result = source_sink_start_ep(ss, false, true, speed);
		if (result < 0) {
			usb_ep_disable(ep);
			goto fail3;
		}
	}
out:
	ss->cur_alt = alt;

	DBG(cdev, "%s enabled, alt intf %d\n", ss->function.name, alt);
	return result;
}