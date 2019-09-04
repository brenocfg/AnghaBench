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
struct usb_request {int /*<<< orphan*/  buf; } ;
struct usb_gadget {int dummy; } ;
struct fsg_lun {scalar_t__ registered; int /*<<< orphan*/  dev; } ;
struct fsg_dev {scalar_t__ state; int nluns; int /*<<< orphan*/  ep0; TYPE_1__* buffhds; struct fsg_lun* luns; int /*<<< orphan*/  thread_notifier; int /*<<< orphan*/  atomic_bitflags; struct usb_request* ep0req; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct fsg_dev*,char*) ; 
 int /*<<< orphan*/  FSG_STATE_EXIT ; 
 scalar_t__ FSG_STATE_TERMINATED ; 
 int /*<<< orphan*/  REGISTERED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_file ; 
 int /*<<< orphan*/  dev_attr_nofua ; 
 int /*<<< orphan*/  dev_attr_ro ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsg_lun_close (struct fsg_lun*) ; 
 int fsg_num_buffers ; 
 struct fsg_dev* get_gadget_data (struct usb_gadget*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raise_exception (struct fsg_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gadget_data (struct usb_gadget*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,struct usb_request*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void /* __init_or_exit */ fsg_unbind(struct usb_gadget *gadget)
{
	struct fsg_dev		*fsg = get_gadget_data(gadget);
	int			i;
	struct fsg_lun		*curlun;
	struct usb_request	*req = fsg->ep0req;

	DBG(fsg, "unbind\n");
	clear_bit(REGISTERED, &fsg->atomic_bitflags);

	/* If the thread isn't already dead, tell it to exit now */
	if (fsg->state != FSG_STATE_TERMINATED) {
		raise_exception(fsg, FSG_STATE_EXIT);
		wait_for_completion(&fsg->thread_notifier);

		/* The cleanup routine waits for this completion also */
		complete(&fsg->thread_notifier);
	}

	/* Unregister the sysfs attribute files and the LUNs */
	for (i = 0; i < fsg->nluns; ++i) {
		curlun = &fsg->luns[i];
		if (curlun->registered) {
			device_remove_file(&curlun->dev, &dev_attr_nofua);
			device_remove_file(&curlun->dev, &dev_attr_ro);
			device_remove_file(&curlun->dev, &dev_attr_file);
			fsg_lun_close(curlun);
			device_unregister(&curlun->dev);
			curlun->registered = 0;
		}
	}

	/* Free the data buffers */
	for (i = 0; i < fsg_num_buffers; ++i)
		kfree(fsg->buffhds[i].buf);

	/* Free the request and buffer for endpoint 0 */
	if (req) {
		kfree(req->buf);
		usb_ep_free_request(fsg->ep0, req);
	}

	set_gadget_data(gadget, NULL);
}