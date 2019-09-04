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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct port100 {int /*<<< orphan*/  out_urb_lock; TYPE_2__* out_urb; TYPE_1__* in_urb; scalar_t__ cmd_cancel; } ;
struct TYPE_5__ {int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; } ;
struct TYPE_4__ {int transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int port100_submit_urb_for_ack (struct port100*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unlink_urb (TYPE_2__*) ; 

__attribute__((used)) static int port100_send_frame_async(struct port100 *dev, struct sk_buff *out,
				    struct sk_buff *in, int in_len)
{
	int rc;

	mutex_lock(&dev->out_urb_lock);

	/* A command cancel frame as been sent through dev->out_urb. Don't try
	 * to submit a new one.
	 */
	if (dev->cmd_cancel) {
		rc = -EAGAIN;
		goto exit;
	}

	dev->out_urb->transfer_buffer = out->data;
	dev->out_urb->transfer_buffer_length = out->len;

	dev->in_urb->transfer_buffer = in->data;
	dev->in_urb->transfer_buffer_length = in_len;

	print_hex_dump_debug("PORT100 TX: ", DUMP_PREFIX_NONE, 16, 1,
			     out->data, out->len, false);

	rc = usb_submit_urb(dev->out_urb, GFP_KERNEL);
	if (rc)
		goto exit;

	rc = port100_submit_urb_for_ack(dev, GFP_KERNEL);
	if (rc)
		usb_unlink_urb(dev->out_urb);

exit:
	mutex_unlock(&dev->out_urb_lock);

	return rc;
}