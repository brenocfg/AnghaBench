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
struct usb_request {int /*<<< orphan*/ * buf; } ;
struct usb_composite_dev {int dummy; } ;
struct TYPE_6__ {TYPE_1__* config; } ;
struct TYPE_5__ {TYPE_3__ func; } ;
struct f_rndis {int /*<<< orphan*/  notify_count; int /*<<< orphan*/  notify; TYPE_2__ port; struct usb_request* notify_req; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int usb_ep_queue (int /*<<< orphan*/ ,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rndis_response_available(void *_rndis)
{
	struct f_rndis			*rndis = _rndis;
	struct usb_request		*req = rndis->notify_req;
	struct usb_composite_dev	*cdev = rndis->port.func.config->cdev;
	__le32				*data = req->buf;
	int				status;

	if (atomic_inc_return(&rndis->notify_count) != 1)
		return;

	/* Send RNDIS RESPONSE_AVAILABLE notification; a
	 * USB_CDC_NOTIFY_RESPONSE_AVAILABLE "should" work too
	 *
	 * This is the only notification defined by RNDIS.
	 */
	data[0] = cpu_to_le32(1);
	data[1] = cpu_to_le32(0);

	status = usb_ep_queue(rndis->notify, req, GFP_ATOMIC);
	if (status) {
		atomic_dec(&rndis->notify_count);
		DBG(cdev, "notify/0 --> %d\n", status);
	}
}